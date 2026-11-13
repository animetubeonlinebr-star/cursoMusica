#!/usr/bin/env python3
"""Gera os diagramas JPG embutidos nas explicacoes do Modulo 1.

O material grafico (braco da guitarra, formas do CAGED, teclado, ciclo das
quintas, figuras ritmicas) e desenhado aqui, em vez de escrito como arte ASCII
no texto, para que a leitura no painel central seja clara.

As imagens ficam em Source/Course/Content/Diagrams/ e entram no binario por
juce_add_binary_data (ver CMakeLists.txt). Para regerar:

    python3 tools/make_diagrams.py

Dono: ux-ui-designer + musician (os desenhos seguem docs/MUSIC.md).
"""
from __future__ import annotations

import math
import os
from PIL import Image, ImageDraw, ImageFont

# --------------------------------------------------------------------------
# Paleta: os mesmos tokens de Source/UI/Design/Theme.h.
# --------------------------------------------------------------------------
BG = (19, 20, 24)          # #131418
SURFACE = (31, 34, 41)     # #1f2229
RAISED = (42, 46, 55)      # #2a2e37
ACCENT = (123, 69, 201)    # #7b45c9
ACCENT_MUTED = (74, 45, 122)
CYAN = (69, 168, 196)      # #45a8c4
TXT = (248, 248, 248)
TXT2 = (184, 184, 192)
TXT_DIS = (106, 106, 116)
BORDER = (52, 56, 65)      # #343841
DANGER = (240, 80, 88)
SUCCESS = (48, 208, 128)
GOLD = (232, 178, 84)
WOOD = (58, 44, 36)
WOOD_LIGHT = (86, 64, 48)

FONT_DIR = "/usr/share/fonts/truetype/dejavu"
W = 1280
MARGIN = 44

NOTE_SHARP = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"]
# Abertura padrao (Mi grave -> Mi agudo), MIDI + rotulo da corda.
TUNING = [(40, "E"), (45, "A"), (50, "D"), (55, "G"), (59, "B"), (64, "E")]


def font(size: int, bold: bool = False) -> ImageFont.FreeTypeFont:
    name = "DejaVuSans-Bold.ttf" if bold else "DejaVuSans.ttf"
    return ImageFont.truetype(os.path.join(FONT_DIR, name), size)


def note_name(midi: int) -> str:
    return NOTE_SHARP[midi % 12]


def canvas(height: int, bg: int = SURFACE) -> tuple[Image.Image, ImageDraw.ImageDraw]:
    img = Image.new("RGB", (W, height), bg)
    return img, ImageDraw.Draw(img)


def frame(d: ImageDraw.ImageDraw, height: int) -> None:
    d.rounded_rectangle([6, 6, W - 7, height - 7], radius=18, outline=BORDER, width=3)


def title(d: ImageDraw.ImageDraw, text: str, y: int = 30) -> int:
    d.text((MARGIN, y), text, font=font(34, True), fill=TXT, anchor="la")
    d.line([MARGIN, y + 48, W - MARGIN, y + 48], fill=BORDER, width=2)
    return y + 48


def subtitle(d: ImageDraw.ImageDraw, text: str, y: int) -> int:
    d.text((MARGIN, y + 12), text, font=font(20), fill=TXT2, anchor="la")
    return y + 44


# --------------------------------------------------------------------------
# Braco da guitarra (horizontal): pestana a esquerda, casa 12 a direita.
# --------------------------------------------------------------------------
def fretboard(d, x, y, w, h, n_frets=12, start_fret=0, show_notes=True,
              highlight=None, root_pc=None, note_font=None, fret_numbers=True):
    """Braco horizontal; `highlight` destaca pitch classes (0..11)."""
    highlight = set(highlight or [])
    note_font = note_font or font(15, True)
    strings = list(reversed(TUNING))          # corda 1 (aguda) no topo
    n_strings = len(strings)
    fret_w = w / n_frets
    string_gap = h / (n_strings - 1)

    d.rounded_rectangle([x, y, x + w, y + h], radius=10, fill=RAISED,
                        outline=BORDER, width=2)

    # Marcadores de casa (3, 5, 7, 9) e duplo na 12.
    mid_y = y + h / 2
    for f in (3, 5, 7, 9):
        if start_fret < f <= start_fret + n_frets:
            cx = x + (f - start_fret - 0.5) * fret_w
            d.ellipse([cx - 6, mid_y - 6, cx + 6, mid_y + 6], fill=TXT_DIS)
    if start_fret < 12 <= start_fret + n_frets:
        cx = x + (12 - start_fret - 0.5) * fret_w
        for dy in (-13, 13):
            d.ellipse([cx - 6, mid_y + dy - 6, cx + 6, mid_y + dy + 6], fill=TXT_DIS)

    for i in range(1, n_frets + 1):
        cx = x + i * fret_w
        d.line([cx, y + 2, cx, y + h - 2], fill=(150, 150, 160), width=2)
    if start_fret == 0:
        d.line([x, y, x, y + h], fill=TXT, width=7)

    for i in range(n_strings):
        cy = y + i * string_gap
        d.line([x, cy, x + w, cy], fill=(210, 210, 215), width=3 if i < 3 else 4)

    if show_notes:
        for i, (open_midi, _) in enumerate(strings):
            cy = y + i * string_gap
            for f in range(n_frets + 1):
                midi = open_midi + start_fret + f
                pc = midi % 12
                cx = x - 16 if f == 0 else x + (f - 0.5) * fret_w
                if pc in highlight:
                    r = 15
                    d.ellipse([cx - r, cy - r, cx + r, cy + r],
                              fill=ACCENT if pc == root_pc else CYAN)
                    d.text((cx, cy), note_name(midi), font=note_font, fill=TXT, anchor="mm")
                else:
                    d.text((cx, cy), note_name(midi), font=note_font, fill=TXT2, anchor="mm")

    if fret_numbers:
        for f in range(1, n_frets + 1):
            cx = x + (f - 0.5) * fret_w
            d.text((cx, y + h + 22), str(start_fret + f), font=font(16),
                   fill=TXT_DIS, anchor="mm")
        if start_fret == 0:
            d.text((x, y + h + 22), "0", font=font(16), fill=TXT_DIS, anchor="mm")


def string_labels(d, x, y, h, gap_font=None):
    gap_font = gap_font or font(17, True)
    strings = list(reversed(TUNING))
    string_gap = h / (len(strings) - 1)
    for i, (_, name) in enumerate(strings):
        d.text((x, y + i * string_gap), name, font=gap_font, fill=ACCENT, anchor="rm")


# --------------------------------------------------------------------------
# Diagrama de acorde (vertical): corda 1 a direita, casa 1 em cima.
# --------------------------------------------------------------------------
def chord_box(d, cx, cy, w, h, frets, name, start_fret=1, note_font=None, caption=None):
    """`frets`: 6 posicoes da 6a para a 1a corda (-1 = abafada, 0 = solta)."""
    note_font = note_font or font(14, True)
    n_strings, rows = 6, 4
    left, top = cx - w / 2, cy
    string_gap = w / (n_strings - 1)
    fret_gap = h / rows
    strings = list(reversed(TUNING))

    d.text((cx, top - 34), name, font=font(25, True), fill=TXT, anchor="mm")

    for i in range(n_strings):
        x = left + i * string_gap
        d.line([x, top, x, top + h], fill=(190, 190, 200), width=2)
    for r in range(rows + 1):
        yy = top + r * fret_gap
        d.line([left, yy, left + w, yy], fill=(190, 190, 200), width=2)
    if start_fret == 1:
        d.line([left, top, left + w, top], fill=TXT, width=6)
    else:
        d.text((left - 14, top + fret_gap / 2), str(start_fret), font=font(16, True),
               fill=TXT2, anchor="rm")

    for i, f in enumerate(frets):
        x = left + i * string_gap
        if f < 0:
            d.text((x, top - 14), "x", font=font(16, True), fill=DANGER, anchor="mm")
        elif f == 0:
            d.ellipse([x - 7, top - 21, x + 7, top - 7], outline=SUCCESS, width=3)

    played = [(i, f) for i, f in enumerate(frets) if f > 0]
    barre_set = set()
    if played:
        min_f = min(f for _, f in played)
        barre = [i for i, f in played if f == min_f]
        if len(barre) >= 2:
            i0, i1 = min(barre), max(barre)
            yy = top + (min_f - start_fret + 0.5) * fret_gap
            d.rounded_rectangle([left + i0 * string_gap, yy - 11,
                                 left + i1 * string_gap, yy + 11], radius=11, fill=ACCENT)
            barre_set = set(barre)
        for i, f in played:
            if i in barre_set:
                continue
            x = left + i * string_gap
            yy = top + (f - start_fret + 0.5) * fret_gap
            d.ellipse([x - 11, yy - 11, x + 11, yy + 11], fill=ACCENT)

    for i, f in enumerate(frets):
        x = left + i * string_gap
        if f >= 0:
            d.text((x, top + h + 22), note_name(strings[i][0] + f), font=note_font,
                   fill=TXT2, anchor="mm")
    if caption:
        d.text((cx, top + h + 48), caption, font=font(16), fill=TXT_DIS, anchor="mm")


# --------------------------------------------------------------------------
# Teclado.
# --------------------------------------------------------------------------
def piano(d, x, y, w, h, octaves=1, natural_labels=True, black_labels=None):
    white_pcs = [0, 2, 4, 5, 7, 9, 11]
    black_after = {0: 1, 2: 3, 5: 6, 7: 8, 9: 10}
    n_white = len(white_pcs) * octaves + 1
    kw = w / n_white

    for i in range(n_white):
        left = x + i * kw
        d.rectangle([left, y, left + kw - 2, y + h], fill=(238, 238, 240),
                    outline=(120, 120, 128), width=2)
        if natural_labels:
            d.text((left + kw / 2, y + h - 26),
                   f"{NOTE_SHARP[white_pcs[i % 7]]}{4 + i // 7}",
                   font=font(19, True), fill=(40, 40, 46), anchor="mm")

    black_h = h * 0.62
    for i in range(n_white - 1):
        pc = white_pcs[i % 7]
        if pc not in black_after:
            continue
        bpc = black_after[pc]
        left = x + (i + 1) * kw - kw * 0.32
        d.rectangle([left, y, left + kw * 0.64, y + black_h], fill=(28, 28, 34),
                    outline=(90, 90, 100), width=2)
        if black_labels and bpc in black_labels:
            d.text((left + kw * 0.32, y + black_h - 20), black_labels[bpc],
                   font=font(15, True), fill=TXT, anchor="mm")


# --------------------------------------------------------------------------
# Diagramas (um por arquivo).
# --------------------------------------------------------------------------
def d_a_partes_do_instrumento():
    h = 940
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Partes da guitarra e do violao")
    y = subtitle(d, "Cada parte tem uma funcao: sustentar, tensionar, amplificar ou ajustar.", y)
    cx = W // 2

    d.ellipse([cx - 215, 560, cx + 215, 900], fill=WOOD, outline=WOOD_LIGHT, width=4)
    d.ellipse([cx - 160, 430, cx + 160, 640], fill=WOOD, outline=WOOD_LIGHT, width=4)
    d.rectangle([cx - 150, 500, cx + 150, 700], fill=WOOD)
    d.ellipse([cx - 215, 560, cx + 215, 900], outline=WOOD_LIGHT, width=4)
    d.ellipse([cx - 62, 630, cx + 62, 754], fill=(20, 16, 14))
    d.ellipse([cx - 62, 630, cx + 62, 754], outline=GOLD, width=3)
    d.ellipse([cx - 74, 618, cx + 74, 766], outline=(150, 120, 70), width=2)
    d.rectangle([cx - 30, 120, cx + 30, 470], fill=(46, 34, 28), outline=WOOD_LIGHT, width=3)
    for i in range(1, 12):
        yy = 470 - i * 30
        d.line([cx - 30, yy, cx + 30, yy], fill=(200, 200, 205), width=2)
    d.rectangle([cx - 34, 462, cx + 34, 474], fill=(238, 238, 240))
    d.rounded_rectangle([cx - 40, 40, cx + 40, 122], radius=10, fill=WOOD,
                        outline=WOOD_LIGHT, width=3)
    for i in range(3):
        yy = 60 + i * 22
        for sgn in (-1, 1):
            px = cx + sgn * 46
            d.ellipse([px - 9, yy - 9, px + 9, yy + 9], fill=(210, 210, 215),
                      outline=(120, 120, 128), width=2)
    for i in range(6):
        x = cx - 25 + i * 10
        d.line([x, 470, x, 770], fill=(225, 225, 230), width=1 + (i // 3))
    d.rounded_rectangle([cx - 92, 760, cx + 92, 800], radius=6, fill=(30, 24, 20),
                        outline=WOOD_LIGHT, width=3)
    d.rectangle([cx - 84, 768, cx + 84, 776], fill=(235, 235, 240))

    labels = [("Cabeca", 60, 80, "r"), ("Tarraxas", 60, 104, "r"),
              ("Pestana (nut)", 60, 468, "r"), ("Braco / escala", 60, 300, "r"),
              ("Trastes e casas", -60, 360, "l"), ("Cordas", -60, 540, "l"),
              ("Boca / caixa de ressonancia", -120, 690, "l"), ("Corpo", -230, 840, "l"),
              ("Cavalete / ponte", 110, 776, "r"), ("Rastilho", 110, 810, "r")]
    for text, dx, ly, side in labels:
        tx = cx + dx
        d.text((tx, ly), text, font=font(21, True), fill=CYAN,
               anchor="lm" if side == "r" else "rm")
        d.line([tx + (12 if side == "r" else -12), ly, cx + (34 if side == "r" else -34), ly],
               fill=BORDER, width=2)
    return img


def d_b_teclado_notas_naturais():
    h = 520
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "As sete notas naturais no teclado")
    y = subtitle(d, "Do a Do: as notas naturais ficam nas teclas brancas; as pretas sao os acidentes.", y)
    piano(d, MARGIN + 40, y + 40, W - 2 * MARGIN - 80, 260)
    d.text((W / 2, h - 52), "Do  Re  Mi  Fa  Sol  La  Si  Do",
           font=font(22, True), fill=TXT2, anchor="mm")
    return img


def d_b_tons_e_semitons():
    h = 560
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Tom e semitom na escala de Do maior")
    y = subtitle(d, "A escala maior e o padrao T - T - S - T - T - T - S (T = tom, S = semitom).", y)
    piano(d, MARGIN + 40, y + 60, W - 2 * MARGIN - 80, 220)
    steps = ["T", "T", "S", "T", "T", "T", "S"]
    kw = (W - 2 * MARGIN - 80) / 8
    for i, s in enumerate(steps):
        d.text((MARGIN + 40 + (i + 1) * kw, y + 330), s, font=font(24, True),
               fill=GOLD if s == "S" else CYAN, anchor="mm")
    d.text((W / 2, h - 60), "S (semitom) so aparece entre Mi-Fa e Si-Do.",
           font=font(21), fill=TXT2, anchor="mm")
    return img


def d_c_escala_cromatica_corda6():
    h = 620
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Escala cromatica na 6a corda")
    y = subtitle(d, "Cada casa e um semitom: da corda solta (Mi) ate a casa 12 (Mi, uma oitava acima).", y)
    d.text((MARGIN, y + 85), "6a", font=font(20, True), fill=ACCENT, anchor="la")
    fretboard(d, MARGIN + 70, y + 40, W - 2 * MARGIN - 70, 90,
              highlight=set(range(12)), root_pc=4)
    d.text((W / 2, h - 70), "Mi  Fa  Fa#  Sol  Sol#  La  La#  Si  Do  Do#  Re  Re#  Mi",
           font=font(19, True), fill=TXT2, anchor="mm")
    d.text((W / 2, h - 36), "12 casas = 12 semitons = uma oitava.",
           font=font(19), fill=GOLD, anchor="mm")
    return img


def d_c_enarmonia_teclado():
    h = 520
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Enarmonia: dois nomes, um som")
    y = subtitle(d, "Cada tecla preta tem dois nomes (sustenido e bemol) e uma unica altura.", y)
    piano(d, MARGIN + 40, y + 60, W - 2 * MARGIN - 80, 240,
          black_labels={1: "C#/Db", 3: "D#/Eb", 6: "F#/Gb", 8: "G#/Ab", 10: "A#/Bb"})
    d.text((W / 2, h - 56), "Ex.: Fa# e Solb sao a mesma casa no braco.",
           font=font(21, True), fill=GOLD, anchor="mm")
    return img


def d_d_mapa_do_braco():
    h = 760
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Mapa completo do braco (6a a 1a corda)")
    y = subtitle(d, "A mesma nota aparece em varias cordas. Use as casas 5, 7 e 12 como referencia.", y)
    string_labels(d, MARGIN + 30, y + 40, 6 * 62)
    fretboard(d, MARGIN + 50, y + 40, W - 2 * MARGIN - 50, 6 * 62)
    d.text((W / 2, h - 60), "Casa 12 = corda solta uma oitava acima (todas as cordas).",
           font=font(21, True), fill=GOLD, anchor="mm")
    return img


def d_d_mapa_corda_6():
    h = 560
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "A 6a corda: o mapa que orienta a mao")
    y = subtitle(d, "Decorar a 6a corda (e a 5a) nas primeiras casas resolve a maioria dos acordes.", y)
    string_labels(d, MARGIN + 30, y + 40, 90)
    fretboard(d, MARGIN + 50, y + 40, W - 2 * MARGIN - 50, 90,
              highlight=set(range(12)), root_pc=4)
    rows = ["Casa 5 (6a) = La, igual a 5a corda solta.",
            "Casa 7 (6a) = Si; casa 8 = Do; casa 12 = Mi.",
            "Casa 3 (6a) = Sol; casa 1 = Fa."]
    for i, r in enumerate(rows):
        d.text((MARGIN, y + 220 + i * 40), "- " + r, font=font(21), fill=TXT2, anchor="la")
    return img


def d_d_oitavas():
    h = 620
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "O padrao de oitava")
    y = subtitle(d, "Da tonica, pule duas cordas para cima e duas casas para a frente: e a mesma nota.", y)
    for k, label in enumerate(["6a -> 4a", "5a -> 3a"]):
        top = y + 50 + k * 220
        d.text((MARGIN, top), label, font=font(20, True), fill=CYAN, anchor="la")
        string_labels(d, MARGIN + 60, top + 30, 5 * 34, gap_font=font(15, True))
        fretboard(d, MARGIN + 80, top + 30, W - 2 * MARGIN - 80, 5 * 34, n_frets=5,
                  highlight={0, 2, 4, 5, 7, 9, 11}, root_pc=4, note_font=font(13, True))
    d.text((W / 2, h - 52), "Duas cordas acima + duas casas a frente = a mesma nota, uma oitava acima.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_e_pestana_fa():
    h = 620
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Pestana de Fa (forma de Mi na 1a casa)")
    y = subtitle(d, "Um dedo cobre as seis cordas; as outras notas formam o acorde de Fa maior.", y)
    chord_box(d, W / 2, y + 80, 190, 210, [1, 3, 3, 2, 1, 1], "Fa maior (F)",
              start_fret=1, caption="Indicador: pestana na 1a casa")
    d.text((MARGIN, y + 400), "Pestana limpa: dedo logo atras do traste, polegar no meio do braco.",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, y + 440), "Cordas de nylon perdoam mais; nas de aco, pressione com firmeza.",
           font=font(21), fill=TXT2, anchor="la")
    return img


def d_e_meio_barre_bm():
    h = 600
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Meio barre de Si menor (forma de La menor)")
    y = subtitle(d, "O meio barre cobre de 2 a 4 cordas: mais facil que a pestana completa.", y)
    chord_box(d, W / 2, y + 80, 190, 210, [-1, 2, 4, 4, 3, 2], "Si menor (Bm)",
              start_fret=2, caption="Meio barre na 2a casa")
    d.text((MARGIN, y + 400), "O indicador cobre a 1a a 5a corda; a 6a fica abafada (x).",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, y + 440), "Se uma corda abafar, veja o topico E: ajuste o dedo.",
           font=font(21), fill=TXT2, anchor="la")
    return img


def d_f_caged_cinco_formas():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "As cinco formas do CAGED (acorde de Do maior)")
    y = subtitle(d, "As mesmas cinco formas abertas viram moveis com a pestana: Do, La, Sol, Mi, Re.", y)
    forms = [("C", [0, 3, 2, 0, 1, 0], 1), ("A", [-1, 3, 5, 5, 5, 3], 3),
             ("G", [8, 7, 5, 5, 5, 8], 5), ("E", [8, 10, 10, 9, 8, 8], 8),
             ("D", [-1, -1, 10, 9, 8, 8], 8)]
    box_w = (W - 2 * MARGIN) / 5
    for i, (name, frets, start) in enumerate(forms):
        cx = MARGIN + box_w * (i + 0.5)
        chord_box(d, cx, y + 110, 150, 170, frets, name, start_fret=start,
                  caption=f"{start}a casa", note_font=font(12, True))
    d.text((W / 2, h - 56), "Todas soam Do maior; mudam a regiao e o timbre.",
           font=font(22, True), fill=GOLD, anchor="mm")
    return img


def d_f_caged_conexao():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "CAGED: as formas se conectam ao longo do braco")
    y = subtitle(d, "Cada forma termina onde a proxima comeca: C - A - G - E - D - C (uma oitava acima).", y)
    board_y = y + 70
    board_h = 6 * 62
    string_labels(d, MARGIN + 30, board_y, board_h)
    fretboard(d, MARGIN + 50, board_y, W - 2 * MARGIN - 50, board_h,
              highlight={0, 4, 7}, root_pc=0)
    board_x = MARGIN + 50
    board_w = W - 2 * MARGIN - 50
    for name, a, b in [("C", 0, 3), ("A", 3, 5), ("G", 5, 8), ("E", 8, 10), ("D", 10, 12)]:
        x0 = board_x + a * board_w / 12
        x1 = board_x + b * board_w / 12
        d.rectangle([x0, board_y + board_h + 34, x1, board_y + board_h + 66],
                    fill=ACCENT_MUTED, outline=BORDER, width=2)
        d.text(((x0 + x1) / 2, board_y + board_h + 50), name, font=font(22, True),
               fill=TXT, anchor="mm")
    d.text((W / 2, h - 56), "A tonica (Do) esta destacada em violeta em cada regiao.",
           font=font(21, True), fill=GOLD, anchor="mm")
    return img


def d_f_caged_escala():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "CAGED e escalas: cada forma traz a escala de Do maior")
    y = subtitle(d, "Onde ha um acorde ha tambem as notas da escala. Tonica em violeta, quinta em ciano.", y)
    string_labels(d, MARGIN + 30, y + 70, 6 * 60)
    fretboard(d, MARGIN + 50, y + 70, W - 2 * MARGIN - 50, 6 * 60,
              highlight={0, 2, 4, 5, 7, 9, 11}, root_pc=0)
    d.text((W / 2, h - 90), "Notas da escala de Do maior nas 12 primeiras casas.",
           font=font(21), fill=TXT2, anchor="mm")
    d.text((W / 2, h - 52), "Tonica (Do) e quinta (Sol) resolvem a frase.",
           font=font(21, True), fill=GOLD, anchor="mm")
    return img


def d_g_ciclo_das_quintas():
    h = 900
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "O circulo das quintas")
    y = subtitle(d, "Subindo de quinta em quinta: a cada passo ganha-se um sustenido (sentido horario).", y)
    cx, cy = W / 2, y + 380
    r_out, r_in = 300, 210
    majors = ["C", "G", "D", "A", "E", "B", "F#/Gb", "C#/Db", "G#/Ab", "D#/Eb", "A#/Bb", "F"]
    minors = ["Am", "Em", "Bm", "F#m", "C#m", "G#m", "D#m/Ebm", "A#m/Bbm", "Fm", "Cm", "Gm", "Dm"]
    for i in range(12):
        d.pieslice([cx - r_out, cy - r_out, cx + r_out, cy + r_out],
                   start=-90 + i * 30 - 15, end=-90 + i * 30 + 15,
                   fill=RAISED if i % 2 == 0 else SURFACE, outline=BORDER)
        am = math.radians(-90 + i * 30)
        d.text((cx + (r_out - 52) * math.cos(am), cy + (r_out - 52) * math.sin(am)),
               majors[i], font=font(26, True), fill=TXT, anchor="mm")
        d.text((cx + (r_in - 46) * math.cos(am), cy + (r_in - 46) * math.sin(am)),
               minors[i], font=font(18), fill=CYAN, anchor="mm")
    d.ellipse([cx - 120, cy - 120, cx + 120, cy + 120], fill=ACCENT_MUTED,
              outline=BORDER, width=2)
    d.text((cx, cy - 14), "CIRCULO", font=font(22, True), fill=TXT, anchor="mm")
    d.text((cx, cy + 18), "DAS QUINTAS", font=font(22, True), fill=TXT, anchor="mm")
    d.text((MARGIN, h - 100), "Anel externo: tonalidade maior.  Anel interno: relativa menor.",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 62), "Ir para a esquerda (quartas) acrescenta um bemol.",
           font=font(21), fill=GOLD, anchor="la")
    return img


def d_g_campo_harmonico_do():
    h = 660
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Campo harmonico maior de Do")
    y = subtitle(d, "Os sete acordes que nascem da escala: I ii iii IV V vi vii - com suas funcoes.", y)
    chords = [("C", "I", "tonica", [0, 3, 2, 0, 1, 0]), ("Dm", "ii", "subdominante", [-1, -1, 0, 2, 3, 1]),
              ("Em", "iii", "tonica relativa", [0, 2, 2, 0, 0, 0]), ("F", "IV", "subdominante", [1, 3, 3, 2, 1, 1]),
              ("G", "V", "dominante", [3, 2, 0, 0, 0, 3]), ("Am", "vi", "relativa menor", [-1, 0, 2, 2, 1, 0]),
              ("Bdim", "vii", "sensivel", [-1, 2, 3, 4, 3, -1])]
    bw = (W - 2 * MARGIN) / 4
    for i, (name, deg, func, frets) in enumerate(chords):
        cx = MARGIN + bw * (i % 4 + 0.5)
        cy = y + 70 + (i // 4) * 280
        chord_box(d, cx, cy, 120, 130, frets, f"{name} ({deg})", start_fret=1,
                  caption=func, note_font=font(12, True))
    return img


def d_h_cifras_acordes():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Lendo a cifra: o mesmo Do em seis formas")
    y = subtitle(d, "A letra da o nome; os simbolos dizem a qualidade do acorde.", y)
    chords = [("C", "maior", [0, 3, 2, 0, 1, 0], 1), ("Cm", "menor", [-1, 3, 5, 5, 4, 3], 3),
              ("C7", "setima dominante", [-1, 3, 2, 3, 1, 0], 1), ("C7M", "setima maior", [-1, 3, 2, 0, 0, 0], 1),
              ("Cm7", "menor com setima", [-1, 3, 5, 3, 4, 3], 3), ("C/E", "com Mi no baixo", [0, 3, 2, 0, 1, 0], 1)]
    bw = (W - 2 * MARGIN) / 3
    for i, (name, cap, frets, start) in enumerate(chords):
        cx = MARGIN + bw * (i % 3 + 0.5)
        cy = y + 80 + (i // 3) * 290
        chord_box(d, cx, cy, 140, 150, frets, name, start_fret=start, caption=cap,
                  note_font=font(12, True))
    return img


def d_h_tablatura():
    h = 620
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Tablatura: a posicao no braco escrita em numeros")
    y = subtitle(d, "Cada linha e uma corda; cada numero e a casa onde o dedo pressiona.", y)
    x0, x1 = MARGIN + 70, W - MARGIN - 40
    lines = ["e", "B", "G", "D", "A", "E"]
    top, gap = y + 70, 56
    for i, name in enumerate(lines):
        yy = top + i * gap
        d.line([x0, yy, x1, yy], fill=(190, 190, 200), width=2)
        d.text((x0 - 24, yy), name, font=font(22, True), fill=ACCENT, anchor="rm")
    # Escala de Do maior subindo pelas cordas (linha 0 = 1a corda).
    seq = [(4, "3"), (2, "2"), (2, "3"), (3, "2"), (3, "5"), (2, "3"),
           (2, "5"), (1, "3"), (1, "5"), (1, "8")]
    col_w = (x1 - x0) / (len(seq) + 1)
    for k, (line_idx, fret) in enumerate(seq):
        xx = x0 + (k + 1) * col_w
        yy = top + line_idx * gap
        d.rounded_rectangle([xx - 15, yy - 16, xx + 15, yy + 16], radius=6,
                            fill=ACCENT_MUTED, outline=ACCENT, width=2)
        d.text((xx, yy), fret, font=font(20, True), fill=TXT, anchor="mm")
    d.text((MARGIN, h - 90), "Exemplo: escala de Do maior subindo pelas cordas.",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 52), "Tablatura nao diz o ritmo: para isso, use a cifra ou a partitura.",
           font=font(21), fill=GOLD, anchor="la")
    return img


def _note_glyph(d, cx, cy, kind, color=TXT):
    hollow = kind in ("whole", "half")
    rw, rh = 22, 15
    d.ellipse([cx - rw, cy - rh, cx + rw, cy + rh],
              fill=color if not hollow else None, outline=color, width=3)
    if kind == "whole":
        return
    stem_x = cx + rw - 2
    d.line([stem_x, cy, stem_x, cy - 62], fill=color, width=3)
    if kind in ("eighth", "sixteenth"):
        for k in range(1 if kind == "eighth" else 2):
            fy = cy - 62 + k * 20
            d.line([stem_x, fy, stem_x + 26, fy + 16], fill=color, width=3)


def d_i_figuras_ritmicas():
    h = 680
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Figuras ritmicas e seus valores")
    y = subtitle(d, "Cada figura vale metade da anterior. A silaba ajuda a contar em voz alta.", y)
    figures = [("whole", "Semibreve", "4 tempos", "TA-A-A-A", 620),
               ("half", "Minima", "2 tempos", "TA-A", 310),
               ("quarter", "Seminima", "1 tempo", "TA", 155),
               ("eighth", "Colcheia", "1/2 tempo", "TA-KI", 78),
               ("sixteenth", "Semicolcheia", "1/4 tempo", "TA-KI-TA-KI", 39)]
    top = y + 80
    for i, (kind, name, value, syll, bar_w) in enumerate(figures):
        yy = top + i * 92
        _note_glyph(d, MARGIN + 70, yy + 30, kind)
        d.text((MARGIN + 150, yy + 6), name, font=font(26, True), fill=TXT, anchor="la")
        d.text((MARGIN + 150, yy + 44), f"{value}   -   {syll}", font=font(21),
               fill=CYAN, anchor="la")
        d.rounded_rectangle([MARGIN + 700, yy + 14, MARGIN + 700 + bar_w, yy + 50],
                            radius=6, fill=ACCENT_MUTED)
    d.text((W / 2, h - 52), "Semibreve = 4x seminima. Cada subdivisao dobra a quantidade de notas.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_i_compasso_4_4():
    h = 620
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Compasso 4/4: quatro tempos, subdivididos")
    y = subtitle(d, "O numero de cima diz quantos tempos; o de baixo, qual figura vale um tempo.", y)
    x0, x1 = MARGIN + 90, W - MARGIN - 40
    top = y + 70
    beat_w = (x1 - x0) / 4
    d.text((MARGIN + 40, top + 10), "4", font=font(40, True), fill=ACCENT, anchor="mm")
    d.text((MARGIN + 40, top + 56), "4", font=font(40, True), fill=ACCENT, anchor="mm")
    d.line([MARGIN + 40, top + 33, MARGIN + 66, top + 33], fill=ACCENT, width=3)
    d.line([x0, top - 10, x0, top + 150], fill=TXT, width=4)
    d.line([x1, top - 10, x1, top + 150], fill=TXT, width=4)
    d.line([x0, top - 10, x1, top - 10], fill=TXT, width=4)
    d.line([x0, top + 150, x1, top + 150], fill=TXT, width=4)
    for b in range(4):
        bx = x0 + b * beat_w
        if b > 0:
            d.line([bx, top - 10, bx, top + 150], fill=BORDER, width=2)
        d.text((bx + beat_w / 2, top + 30), str(b + 1), font=font(34, True), fill=TXT, anchor="mm")
        d.text((bx + beat_w / 2, top + 76), "TA", font=font(24, True), fill=CYAN, anchor="mm")
        d.text((bx + beat_w / 2, top + 116), "TA-KI", font=font(20), fill=TXT2, anchor="mm")
    d.text((MARGIN, h - 96), "Contar '1 e 2 e 3 e 4 e' (ou TA-KI) antes de tocar alinha ao metronomo.",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 56), "O gate cobra tocar na grade (on_grid_ratio >= 0,75).",
           font=font(21, True), fill=GOLD, anchor="la")
    return img


DIAGRAMS = {
    "a_partes_do_instrumento": d_a_partes_do_instrumento,
    "b_teclado_notas_naturais": d_b_teclado_notas_naturais,
    "b_tons_e_semitons": d_b_tons_e_semitons,
    "c_escala_cromatica_corda6": d_c_escala_cromatica_corda6,
    "c_enarmonia_teclado": d_c_enarmonia_teclado,
    "d_mapa_do_braco": d_d_mapa_do_braco,
    "d_mapa_corda_6": d_d_mapa_corda_6,
    "d_oitavas": d_d_oitavas,
    "e_pestana_fa": d_e_pestana_fa,
    "e_meio_barre_bm": d_e_meio_barre_bm,
    "f_caged_cinco_formas": d_f_caged_cinco_formas,
    "f_caged_conexao": d_f_caged_conexao,
    "f_caged_escala": d_f_caged_escala,
    "g_ciclo_das_quintas": d_g_ciclo_das_quintas,
    "g_campo_harmonico_do": d_g_campo_harmonico_do,
    "h_cifras_acordes": d_h_cifras_acordes,
    "h_tablatura": d_h_tablatura,
    "i_figuras_ritmicas": d_i_figuras_ritmicas,
    "i_compasso_4_4": d_i_compasso_4_4,
}


def main() -> None:
    out_dir = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                           "Source", "Course", "Content", "Diagrams")
    os.makedirs(out_dir, exist_ok=True)
    total = 0
    for name, fn in DIAGRAMS.items():
        img = fn()
        path = os.path.join(out_dir, name + ".jpg")
        img.save(path, "JPEG", quality=88, optimize=True)
        size = os.path.getsize(path)
        total += size
        print(f"{name}.jpg  {img.width}x{img.height}  {size // 1024} KB")
    print(f"{len(DIAGRAMS)} diagramas, {total // 1024} KB no total -> {out_dir}")


if __name__ == "__main__":
    main()
