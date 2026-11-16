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


# --------------------------------------------------------------------------
# Modulo 2 — teoria dos intervalos e percepcao musical.
# --------------------------------------------------------------------------
LETTERS = {"C": 0, "D": 1, "E": 2, "F": 3, "G": 4, "A": 5, "B": 6}
STAFF_LINE_GAP = 26


def diatonic_index(name: str, octave: int) -> int:
    return octave * 7 + LETTERS[name[0]]


def staff(d, x, y, w, notes, clef=True, caption=None):
    """Pauta simples (clave de sol). `notes` = [(letter, octave, accidental)]."""
    gap = STAFF_LINE_GAP
    top = y + gap * 2  # linha de cima (F5)
    bottom = y + gap * 6  # linha de baixo (E4)
    d.text((x, y - 34), "Clave de sol", font=font(17, True), fill=TXT2, anchor="la")

    for i in range(5):
        yy = top + i * gap
        d.line([x, yy, x + w, yy], fill=(200, 200, 210), width=2)

    if clef:
        # The DejaVu fonts used here have no treble-clef glyph, so a bold "G"
        # stands in for the clef and the caption names it.
        d.text((x + 6, (top + bottom) / 2), "G", font=font(70, True), fill=TXT, anchor="lm")

    ref = diatonic_index("E", 4)
    step = w / (len(notes) + 1)
    for i, (letter, octave, accidental) in enumerate(notes):
        cx = x + step * (i + 1)
        pos = diatonic_index(letter, octave) - ref
        cy = bottom - pos * (gap / 2)
        rw, rh = 13, 9
        d.ellipse([cx - rw, cy - rh, cx + rw, cy + rh], fill=TXT)
        d.line([cx + rw - 2, cy, cx + rw - 2, cy - 58], fill=TXT, width=3)
        if accidental:
            d.text((cx - rw - 16, cy), accidental, font=font(26, True), fill=GOLD, anchor="mm")

    if caption:
        d.text((x + w / 2, bottom + 78), caption, font=font(20), fill=TXT2, anchor="mm")
    return bottom + 110


def d_m2_semitons_piano():
    h = 560
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Semitons: a regua de todo intervalo")
    y = subtitle(d, "1 semitom = 1 casa no braco = tecla vizinha no teclado. 1 tom = 2 semitons.", y)
    piano(d, MARGIN, y + 40, W - 2 * MARGIN, 240, octaves=2,
          black_labels={1: "C#", 3: "D#", 6: "F#", 8: "G#", 10: "A#"})
    d.text((W / 2, h - 96), "Do ao Do seguinte: 12 semitons (uma oitava).",
           font=font(22, True), fill=CYAN, anchor="mm")
    d.text((W / 2, h - 54), "Entre Mi-Fa e Si-Do ha apenas 1 semitom; as outras notas naturais estao a 1 tom.",
           font=font(19), fill=GOLD, anchor="mm")
    return img


def d_m2_quadro_movel():
    h = 760
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Quadro movel de intervalos (a partir de Do)")
    y = subtitle(d, "Mesmo desenho em qualquer tonica: muda a nota, o nome do intervalo nao.", y)
    rows = [(0, "unissono", "Do"), (1, "2a menor", "Do#"), (2, "2a maior", "Re"),
            (3, "3a menor", "Re#"), (4, "3a maior", "Mi"), (5, "4a justa", "Fa"),
            (6, "4a aum. (tritono)", "Fa#"), (7, "5a justa", "Sol"),
            (8, "6a menor", "Sol#"), (9, "6a maior", "La"), (10, "7a menor", "La#"),
            (11, "7a maior", "Si"), (12, "8a justa", "Do")]
    col_w = (W - 2 * MARGIN) / 3
    top = y + 26
    d.text((MARGIN, top), "Semitons", font=font(19, True), fill=ACCENT, anchor="la")
    d.text((MARGIN + col_w, top), "Intervalo", font=font(19, True), fill=ACCENT, anchor="la")
    d.text((MARGIN + 2 * col_w, top), "Nota", font=font(19, True), fill=ACCENT, anchor="la")
    for i, (semi, name, note) in enumerate(rows):
        yy = top + 30 + i * 48
        fill = RAISED if i % 2 == 0 else SURFACE
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 42], radius=8, fill=fill)
        color = GOLD if semi == 6 else TXT
        d.text((MARGIN + 14, yy + 21), str(semi), font=font(20, True), fill=color, anchor="lm")
        d.text((MARGIN + col_w + 14, yy + 21), name, font=font(20, True), fill=color, anchor="lm")
        d.text((MARGIN + 2 * col_w + 14, yy + 21), note, font=font(20, True), fill=CYAN, anchor="lm")
    return img


def d_m2_mapa_intervalos():
    h = 760
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Intervalos no braco (a partir de Do na 5a corda)")
    y = subtitle(d, "Cada corda e uma regua de semitons; a forma se repete em qualquer tonica.", y)
    fretboard(d, MARGIN + 40, y + 40, W - 2 * MARGIN - 80, 300,
              n_frets=12, start_fret=0, show_notes=True, highlight={0, 4, 7}, root_pc=0)
    string_labels(d, MARGIN + 10, y + 40, 300)
    d.text((MARGIN, h - 118), "Destaques: tonica (0, roxo), terca maior (4, ciano) e quinta justa (7, ciano).",
           font=font(20), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 76), "Ache a tonica e conte os semitons para localizar qualquer intervalo.",
           font=font(20, True), fill=GOLD, anchor="la")
    return img


def d_m2_percepcao_referencias():
    h = 660
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Referencias sonoras por intervalo")
    y = subtitle(d, "Associe cada intervalo a uma sensacao; o ouvido memoriza pela comparacao.", y)
    items = [("2a maior", "passo de escala", "movimento"),
             ("3a maior", "melodia alegre", "aberto"),
             ("3a menor", "melodia triste", "fechado"),
             ("4a justa", "toque de chamada", "firme"),
             ("5a justa", "som vazio/epico", "grandioso"),
             ("6a maior", "frase doce", "expansivo"),
             ("7a maior", "brilho suspenso", "tenso"),
             ("8a justa", "mesma nota mais alta", "identico")]
    top = y + 40
    for i, (name, ref, feel) in enumerate(items):
        yy = top + i * 60
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 52], radius=8, fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 18, yy + 26), name, font=font(22, True), fill=ACCENT, anchor="lm")
        d.text((MARGIN + 260, yy + 26), ref, font=font(20), fill=TXT, anchor="lm")
        d.text((MARGIN + 720, yy + 26), feel, font=font(20, True), fill=CYAN, anchor="lm")
    return img


def d_m2_triades_empilhadas():
    h = 680
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Tríades e tetrades: intervalos empilhados")
    y = subtitle(d, "O nome do acorde descreve os intervalos sobre a tonica.", y)
    groups = [("Maior (0,4,7)", ["Do", "Mi", "Sol"], ACCENT),
              ("Menor (0,3,7)", ["Do", "Mib", "Sol"], CYAN),
              ("7a maior (0,4,7,11)", ["Do", "Mi", "Sol", "Si"], SUCCESS),
              ("7a dominante (0,4,7,10)", ["Do", "Mi", "Sol", "Sib"], GOLD)]
    top = y + 40
    for i, (name, notes, color) in enumerate(groups):
        yy = top + i * 130
        d.text((MARGIN, yy + 10), name, font=font(24, True), fill=color, anchor="la")
        for k, note in enumerate(notes):
            cx = MARGIN + 40 + k * 130
            cy = yy + 74
            d.ellipse([cx - 40, cy - 40, cx + 40, cy + 40], fill=RAISED, outline=color, width=3)
            d.text((cx, cy), note, font=font(24, True), fill=TXT, anchor="mm")
    d.text((W / 2, h - 46), "Cada bolinha e uma nota a um numero de semitons da tonica.",
           font=font(20), fill=TXT2, anchor="mm")
    return img


def d_m2_cantar_tocar():
    h = 520
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "O ciclo do treino de intervalos")
    y = subtitle(d, "Ouvir, cantar, tocar e conferir: cada passo reforca o anterior.", y)
    steps = [("1. Ouvir", "o app demonstra o intervalo"),
             ("2. Cantar", "reproduza a altura com a voz"),
             ("3. Tocar", "execute no braco, em qualquer posicao"),
             ("4. Conferir", "o app mede os semitons e valida")]
    top = y + 50
    for i, (title_txt, desc) in enumerate(steps):
        yy = top + i * 90
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 74], radius=10, fill=RAISED)
        d.text((MARGIN + 20, yy + 22), title_txt, font=font(26, True), fill=ACCENT, anchor="la")
        d.text((MARGIN + 300, yy + 26), desc, font=font(21), fill=TXT, anchor="la")
        if i < len(steps) - 1:
            d.text((W / 2, yy + 78), "v", font=font(24, True), fill=TXT_DIS, anchor="mm")
    return img


def _score_image(name, notes, caption):
    h = 420
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, caption)
    staff(d, MARGIN + 30, y + 40, W - 2 * MARGIN - 60, notes)
    return img


def d_m2_partitura_terca():
    return _score_image("terca", [("C", 4, None), ("E", 4, None)],
                        "Partitura: terca maior (Do-Mi)")


def d_m2_partitura_tercas():
    return _score_image("tercas", [("C", 4, None), ("E", 4, None), ("C", 4, None), ("E", 4, "b")],
                        "Partitura: terca maior e terca menor (Do-Mi / Do-Mib)")


def d_m2_partitura_triade():
    return _score_image("triade", [("C", 4, None), ("E", 4, None), ("G", 4, None), ("C", 5, None)],
                        "Partitura: triade de Do maior com a oitava")


def d_m2_partitura_intervalos():
    return _score_image("intervalos", [("C", 4, None), ("D", 4, None), ("E", 4, None), ("F", 4, None),
                                       ("G", 4, None), ("A", 4, None), ("B", 4, None), ("C", 5, None)],
                        "Partitura: escala de Do maior (cada passo e um intervalo)")


def d_m2_partitura_arpejo():
    return _score_image("arpejo", [("C", 4, None), ("E", 4, None), ("G", 4, None), ("C", 5, None),
                                   ("G", 4, None), ("E", 4, None), ("C", 4, None)],
                        "Partitura: arpejo de Do maior (sobe e desce)")


DIAGRAMS.update({
    "m2_semitons_piano": d_m2_semitons_piano,
    "m2_quadro_movel": d_m2_quadro_movel,
    "m2_mapa_intervalos": d_m2_mapa_intervalos,
    "m2_percepcao_referencias": d_m2_percepcao_referencias,
    "m2_triades_empilhadas": d_m2_triades_empilhadas,
    "m2_cantar_tocar": d_m2_cantar_tocar,
    "m2_partitura_terca": d_m2_partitura_terca,
    "m2_partitura_tercas": d_m2_partitura_tercas,
    "m2_partitura_triade": d_m2_partitura_triade,
    "m2_partitura_intervalos": d_m2_partitura_intervalos,
    "m2_partitura_arpejo": d_m2_partitura_arpejo,
})


def d_m2_qualidades_grupos():
    h = 620
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Os tres grupos de qualidade")
    y = subtitle(d, "Justos; maiores/menores; aumentados/diminutos. O numero diz o grupo.", y)
    cols = [("Justos", ["1a unissono", "4a", "5a", "8a"], ACCENT),
            ("Maiores/Menores", ["2a", "3a", "6a", "7a"], CYAN),
            ("Alterados", ["aumentado", "diminuto"], GOLD)]
    top = y + 40
    col_w = (W - 2 * MARGIN) / 3
    for c, (name, items, color) in enumerate(cols):
        x = MARGIN + c * col_w
        d.rounded_rectangle([x + 10, top, x + col_w - 10, top + 300], radius=12, fill=RAISED)
        d.text((x + col_w / 2, top + 30), name, font=font(24, True), fill=color, anchor="mm")
        for i, it in enumerate(items):
            d.text((x + col_w / 2, top + 80 + i * 44), it, font=font(21), fill=TXT, anchor="mm")
    d.text((W / 2, h - 60), "Justos nao tem versao maior/menor; os demais podem ser alterados.",
           font=font(20), fill=TXT2, anchor="mm")
    return img


def d_m2_intervalos_papeis():
    h = 660
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "O papel de cada intervalo")
    y = subtitle(d, "Cada intervalo tem uma funcao na construcao da musica.", y)
    items = [("terca maior", "define o acorde maior", "aberto"),
             ("terca menor", "define o acorde menor", "fechado"),
             ("quarta justa", "movimento e suspensao", "firme"),
             ("quinta justa", "estabilidade e power chord", "cheio"),
             ("sexta maior", "melodia doce", "expansivo"),
             ("setima maior", "brilho no acorde de setima", "suspenso"),
             ("setima menor", "dominante e blues", "tenso"),
             ("nona", "cor sobre o acorde", "rico")]
    top = y + 34
    for i, (name, role, feel) in enumerate(items):
        yy = top + i * 56
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 48], radius=8,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 18, yy + 24), name, font=font(21, True), fill=ACCENT, anchor="lm")
        d.text((MARGIN + 340, yy + 24), role, font=font(20), fill=TXT, anchor="lm")
        d.text((MARGIN + 900, yy + 24), feel, font=font(20, True), fill=CYAN, anchor="lm")
    return img

DIAGRAMS.update({
    "m2_qualidades_grupos": d_m2_qualidades_grupos,
    "m2_intervalos_papeis": d_m2_intervalos_papeis,
})


# --------------------------------------------------------------------------
# Modulo 3 — ritmo, leitura e levadas.
# --------------------------------------------------------------------------
def _rhythm_row(d, x, y, w, cells, gap_after=0):
    """Faixa de figuras ritmicas: `cells` = [(kind, silaba)] em uma linha."""
    n = len(cells)
    step = w / max(1, n)
    for i, (kind, syll) in enumerate(cells):
        cx = x + step * (i + 0.5)
        _note_glyph(d, cx, y, kind, ACCENT)
        d.text((cx, y + 46), syll, font=font(18, True), fill=CYAN, anchor="mm")
    return y + gap_after


def _bullets(d, y, items, color=ACCENT):
    for i, item in enumerate(items):
        yy = y + i * 54
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 46], radius=8,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 18, yy + 23), item[0], font=font(21, True), fill=color, anchor="lm")
        d.text((MARGIN + 300, yy + 23), item[1], font=font(20), fill=TXT, anchor="lm")
        if len(item) > 2:
            d.text((W - MARGIN - 18, yy + 23), item[2], font=font(19), fill=TXT2, anchor="rm")
    return y + len(items) * 54


def d_m3_leitura_ritmica():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Leitura ritmica: figuras, valores e silabas")
    y = subtitle(d, "Cada figura vale metade da anterior; a silaba ajuda a contar em voz alta.", y)
    figures = [("whole", "Semibreve", "4 tempos", "TA-A-A-A"),
               ("half", "Minima", "2 tempos", "TA-A"),
               ("quarter", "Seminima", "1 tempo", "TA"),
               ("eighth", "Colcheia", "1/2 tempo", "TA-KI"),
               ("sixteenth", "Semicolcheia", "1/4 tempo", "TA-KI-TA-KI")]
    top = y + 70
    for i, (kind, name, value, syll) in enumerate(figures):
        yy = top + i * 88
        _note_glyph(d, MARGIN + 60, yy + 26, kind)
        d.text((MARGIN + 130, yy + 4), name, font=font(25, True), fill=TXT, anchor="la")
        d.text((MARGIN + 130, yy + 40), f"{value}   -   {syll}", font=font(20),
               fill=CYAN, anchor="la")
        d.rounded_rectangle([MARGIN + 620, yy + 12, W - MARGIN, yy + 44], radius=6,
                            fill=ACCENT_MUTED)
        d.text((MARGIN + 636, yy + 28), "contar antes de tocar", font=font(18), fill=TXT2, anchor="lm")
    d.text((W / 2, h - 52), "Ler o ritmo e contar a subdivisao: a base de tocar na grade.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m3_pulsacao_subdivisao():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Pulsacao e subdivisao")
    y = subtitle(d, "O pulso e constante; a subdivisao divide cada pulso em partes iguais.", y)
    x0, x1 = MARGIN + 80, W - MARGIN - 20
    top = y + 90
    beat_w = (x1 - x0) / 4
    d.line([x0, top - 20, x1, top - 20], fill=TXT, width=3)
    for b in range(4):
        bx = x0 + b * beat_w
        d.line([bx, top - 30, bx, top + 150], fill=BORDER, width=2)
        d.text((bx + beat_w / 2, top), "1", font=font(30, True), fill=TXT, anchor="mm")
        d.text((bx + beat_w / 2, top + 46), "TA", font=font(22, True), fill=CYAN, anchor="mm")
        d.text((bx + beat_w / 2, top + 88), "TA-KI", font=font(20), fill=TXT2, anchor="mm")
        d.text((bx + beat_w / 2, top + 126), "TA-KI-TA-KI", font=font(18), fill=TXT_DIS, anchor="mm")
    d.line([x1, top - 30, x1, top + 150], fill=BORDER, width=2)
    d.text((MARGIN, h - 150), "Semínima (1x por pulso) -> colcheia (2x) -> semicolcheia (4x).",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 108), "A subdivisao dobra a cada nivel: e o que o metronomo faz para voce.",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 60), "Tocar na grade = alinhar a nota ao pulso ou a sua subdivisao.",
           font=font(21, True), fill=GOLD, anchor="la")
    return img


def d_m3_cifrado_divisao():
    h = 620
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Cifrado com divisao: o acorde repartido no compasso")
    y = subtitle(d, "A cifra diz o acorde; a divisao diz como ele e tocado no tempo.", y)
    items = [("C", "acorde inteiro no tempo 1", "1 acorde = 1 compasso"),
             ("C  C  C  C", "um acorde por tempo", "4 ataques"),
             ("C  -  G  -", "dois acordes, com contratempo", "ritmo de base"),
             ("C  C/G  C/E", "acorde com baixo (slash chord)", "baixo em movimento"),
             ("C7  C6  C7M", "acordes por grau dentro do compasso", "conducao harmonica")]
    _bullets(d, y + 40, items)
    d.text((W / 2, h - 50), "Ler a cifra e dividir o compasso: e o que transforma o acorde em levada.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m3_celulas_ritmicas():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Celulas ritmicas de acompanhamento")
    y = subtitle(d, "Uma celula e um desenho de ataques que se repete no compasso.", y)
    top = y + 70
    cells = [("Semininas", "TA TA TA TA", ["quarter"] * 4),
             ("Colcheias", "TA-KI TA-KI TA-KI TA-KI", ["eighth"] * 8),
             ("Rock", "TA  TA-KI TA  TA-KI", ["quarter", "eighth", "eighth", "quarter", "eighth", "eighth"]),
             ("Samba", "TA-KI  TA  TA-KI", ["eighth", "eighth", "quarter", "eighth", "eighth"])]
    for i, (name, syll, kinds) in enumerate(cells):
        yy = top + i * 120
        d.text((MARGIN, yy), name, font=font(23, True), fill=ACCENT, anchor="la")
        _rhythm_row(d, MARGIN + 150, yy + 20, W - 2 * MARGIN - 150, [(k, "") for k in kinds])
        d.text((MARGIN + 150, yy + 86), syll, font=font(18), fill=CYAN, anchor="la")
    d.text((W / 2, h - 46), "Repetir a celula mantendo o pulso firme e o que cria o groove.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m3_acentuacoes():
    h = 620
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Acentuacoes: onde o ataque fica forte")
    y = subtitle(d, "Acento (>) reforca um tempo ou contratempo; o resto fica mais leve.", y)
    x0, x1 = MARGIN + 60, W - MARGIN - 20
    top = y + 100
    beat_w = (x1 - x0) / 4
    accented = {0, 2}
    for b in range(4):
        bx = x0 + b * beat_w
        d.line([bx, top - 40, bx, top + 120], fill=BORDER, width=2)
        strong = b in accented
        d.text((bx + beat_w / 2, top), ">", font=font(34, True),
               fill=GOLD if strong else TXT_DIS, anchor="mm")
        d.text((bx + beat_w / 2, top + 54), str(b + 1), font=font(28, True),
               fill=TXT if strong else TXT2, anchor="mm")
        d.text((bx + beat_w / 2, top + 96), "TA", font=font(20, True),
               fill=CYAN if strong else TXT_DIS, anchor="mm")
    d.line([x1, top - 40, x1, top + 120], fill=BORDER, width=2)
    d.text((MARGIN, h - 140), "Tempos fortes (1 e 3) sustentam a danca; fracos (2 e 4) pedem resposta.",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 96), "No samba e no funk o acento cai no contratempo (o 'e' do tempo).",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 52), "Acentuar sem perder o pulso: o detalhe que faz a levada soar viva.",
           font=font(21, True), fill=GOLD, anchor="la")
    return img


def d_m3_levadas_palheta():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Levadas com palheta: direcoes e padroes")
    y = subtitle(d, "A palheta alterna para baixo (v) e para cima (^); o pulso manda.", y)
    top = y + 70
    rows = [("Alternada (colcheias)", ["v", "^", "v", "^", "v", "^", "v", "^"]),
            ("Rock (semininas)", ["v", "v", "v", "v"]),
            ("Palm mute", ["v", "^", "v", "^", "v", "^", "v", "^"]),
            ("Tres por tempo", ["v", "^", "v", "^", "v", "^"])]
    for i, (name, strokes) in enumerate(rows):
        yy = top + i * 120
        d.text((MARGIN, yy + 20), name, font=font(22, True), fill=ACCENT, anchor="la")
        x = MARGIN + 320
        step = (W - MARGIN - 20 - x) / len(strokes)
        for k, s in enumerate(strokes):
            cx = x + step * (k + 0.5)
            d.text((cx, yy + 30), s, font=font(34, True),
                   fill=CYAN if s == "v" else GOLD, anchor="mm")
    d.text((W / 2, h - 46), "Palhetada alternada economiza movimento e mantem o tempo estavel.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m3_direcoes_palheta():
    h = 560
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Palhetada: para baixo e para cima")
    y = subtitle(d, "v = ataque para baixo (mais forte); ^ = ataque para cima (mais leve).", y)
    cx = W / 2
    for i, (symbol, label, color, dy) in enumerate(
            [("v", "downstroke (para baixo)", CYAN, 0), ("^", "upstroke (para cima)", GOLD, 200)]):
        yy = y + 80 + dy
        d.text((cx - 200, yy), symbol, font=font(90, True), fill=color, anchor="mm")
        d.text((cx + 60, yy - 20), label, font=font(28, True), fill=TXT, anchor="lm")
        d.text((cx + 60, yy + 30),
               "ataque no tempo forte" if i == 0 else "ataque no contratempo",
               font=font(21), fill=TXT2, anchor="lm")
    d.text((W / 2, h - 50), "Alternar as direcoes mantem a mao relaxada e o tempo regular.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m3_mapa_mao_direita():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Mapa da mao direita")
    y = subtitle(d, "Polegar, indicador, medio e anelar: cada dedo cuida de um grupo de cordas.", y)
    x0 = MARGIN + 90
    lines = ["e (1a)", "B (2a)", "G (3a)", "D (4a)", "A (5a)", "E (6a)"]
    top, gap = y + 60, 70
    for i, name in enumerate(lines):
        yy = top + i * gap
        d.line([x0, yy, W - MARGIN - 20, yy], fill=(200, 200, 210), width=2)
        d.text((x0 - 20, yy), name, font=font(20, True), fill=ACCENT, anchor="rm")
    fingers = [("polegar (p)", 5, "cordas graves (6a, 5a, 4a)"),
               ("indicador (i)", 2, "3a corda"),
               ("medio (m)", 1, "2a corda"),
               ("anelar (a)", 0, "1a corda")]
    for j, (name, line_idx, desc) in enumerate(fingers):
        yy = top + line_idx * gap
        d.ellipse([x0 + 140 + j * 60 - 16, yy - 16, x0 + 140 + j * 60 + 16, yy + 16],
                  fill=ACCENT if j == 0 else CYAN)
        d.text((W - MARGIN - 20, yy), desc, font=font(18), fill=TXT2, anchor="rm")
    d.text((W / 2, h - 52), "O polegar marca o baixo; os dedos puxam as cordas agudas do acorde.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m3_levadas_dedos():
    h = 660
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Levadas com os dedos (fingerstyle)")
    y = subtitle(d, "Polegar nos tempos, dedos nas cordas agudas: a base da bossa e do violao.", y)
    top = y + 70
    rows = [("Polegar alterna o baixo", ["p", "-", "p", "-", "p", "-", "p", "-"]),
            ("Bossa: polegar + dedos", ["p", "i", "p", "m", "p", "i", "p", "a"]),
            ("Arpejo ascendente", ["p", "i", "m", "a", "p", "i", "m", "a"]),
            ("Travis picking", ["p", "m", "i", "m", "p", "m", "i", "m"])]
    for i, (name, seq) in enumerate(rows):
        yy = top + i * 120
        d.text((MARGIN, yy + 20), name, font=font(22, True), fill=ACCENT, anchor="la")
        x = MARGIN + 360
        step = (W - MARGIN - 20 - x) / len(seq)
        for k, s in enumerate(seq):
            cx = x + step * (k + 0.5)
            color = TXT_DIS if s == "-" else (ACCENT if s == "p" else CYAN)
            d.text((cx, yy + 30), s, font=font(30, True), fill=color, anchor="mm")
    d.text((W / 2, h - 46), "Separar grave e agudo e o que da independencia a mao direita.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m3_compassos():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Compassos simples e compostos")
    y = subtitle(d, "O numero de cima conta os tempos; o de baixo diz qual figura vale 1 tempo.", y)
    items = [("2/4", "dois tempos de seminima", "marcha, baião"),
             ("3/4", "tres tempos de seminima", "valsa"),
             ("4/4", "quatro tempos de seminima", "pop, rock, samba"),
             ("6/8", "seis tempos de colcheia (composto)", "balada, baião"),
             ("12/8", "doze colcheias (composto)", "blues lento, shuffle"),
             ("5/4 e 7/8", "formulas incomuns", "prog rock, jazz moderno")]
    _bullets(d, y + 40, items)
    d.text((W / 2, h - 50), "Simples: subdivide em 2. Composto: subdivide em 3 (o tempo vira tercina).",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m3_formulas_incomuns():
    h = 640
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Formulas de compasso incomuns")
    y = subtitle(d, "Agrupar os tempos em blocos de 2 e 3 mantem a pulsacao compreensivel.", y)
    top = y + 70
    patterns = [("5/4", ["3", "2"], "Take Five"),
                ("5/4", ["2", "3"], "Mission Impossible"),
                ("7/8", ["2", "2", "3"], "prog rock"),
                ("7/8", ["3", "2", "2"], "balkan"),
                ("9/8", ["3", "3", "3"], "compasso composto")]
    for i, (meter, groups, note) in enumerate(patterns):
        yy = top + i * 96
        d.text((MARGIN, yy + 20), meter, font=font(28, True), fill=ACCENT, anchor="la")
        x = MARGIN + 200
        for g in groups:
            w = int(g) * 60
            d.rounded_rectangle([x, yy, x + w - 10, yy + 52], radius=8,
                                fill=RAISED, outline=CYAN, width=2)
            d.text((x + (w - 10) / 2, yy + 26), g, font=font(26, True), fill=CYAN, anchor="mm")
            x += w + 10
        d.text((W - MARGIN, yy + 26), note, font=font(19), fill=TXT2, anchor="rm")
    d.text((W / 2, h - 46), "Contar os grupos (ex.: 1-2-3 / 1-2) e o que torna o compasso tocavel.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m3_konokol():
    h = 660
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Silabas ritmicas (Konokol) e percussao vocal")
    y = subtitle(d, "Falar o ritmo com silabas antes de tocar organiza a subdivisao.", y)
    items = [("TA", "seminima (1 pulso)", "TA"),
             ("TA-KI", "duas colcheias", "TA-KI"),
             ("TA-KI-TA-KI", "quatro semicolcheias", "TA-KI-TA-KI"),
             ("TA-KI-TA", "tres tercinas", "TA-KI-TA"),
             ("TA-KA", "duas partes iguais", "TA-KA"),
             ("DIN", "acento/ataque forte", "DIN")]
    _bullets(d, y + 40, items)
    d.text((W / 2, h - 50), "Falar a celula em voz alta antes de tocar alinha mao, ouvido e tempo.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m3_percussao_sanfona():
    h = 640
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Percussao no violao e efeito sanfona")
    y = subtitle(d, "Bater na madeira e usar o efeito sanfona dao groove sem mudar o acorde.", y)
    items = [("Batida na madeira", "percussao no tampo", "marca o tempo"),
             ("Percussao no cavalete", "som seco e curto", "contratempo"),
             ("Efeito sanfona", "abre e fecha o acorde", "levada de samba/choro"),
             ("Abafamento (mute)", "corda abafada pela mao", "chuck"),
             ("Harmonico percussivo", "toque leve sobre o traste", "cor ritmica")]
    _bullets(d, y + 40, items)
    d.text((W / 2, h - 50), "O efeito sanfona alterna o acorde aberto e abafado, criando pulsacao.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m3_partitura_leitura():
    return _score_image("leitura", [("C", 4, None), ("C", 4, None), ("D", 4, None), ("E", 4, None)],
                        "Partitura: leitura ritmica em Do (contar e tocar)")


def d_m3_partitura_subdivisao():
    return _score_image("subdivisao", [("C", 4, None), ("D", 4, None), ("E", 4, None), ("F", 4, None),
                                       ("G", 4, None), ("F", 4, None), ("E", 4, None), ("D", 4, None)],
                        "Partitura: escala em Do, um passo por pulso")


def d_m3_partitura_cifrado():
    return _score_image("cifrado", [("C", 4, None), ("E", 4, None), ("G", 4, None), ("G", 4, None),
                                    ("E", 4, None), ("C", 4, None)],
                        "Partitura: arpejo de Do maior dividindo o compasso")


def d_m3_partitura_celula():
    return _score_image("celula", [("C", 4, None), ("E", 4, None), ("G", 4, None), ("E", 4, None)],
                        "Partitura: celula de acompanhamento (Do maior)")


def d_m3_partitura_palheta():
    return _score_image("palheta", [("E", 3, None), ("E", 3, None), ("E", 3, None), ("E", 3, None),
                                    ("E", 3, None), ("E", 3, None), ("E", 3, None), ("E", 3, None)],
                        "Partitura: palhetada alternada na corda 6 (Mi)")


def d_m3_partitura_dedos():
    return _score_image("dedos", [("C", 4, None), ("E", 4, None), ("G", 4, None), ("C", 5, None),
                                  ("G", 4, None), ("E", 4, None), ("C", 4, None), ("G", 3, None)],
                        "Partitura: arpejo com os dedos (Do maior)")


def d_m3_partitura_compasso():
    return _score_image("compasso", [("C", 4, None), ("D", 4, None), ("E", 4, None),
                                     ("D", 4, None), ("C", 4, None), ("D", 4, None)],
                        "Partitura: 6/8 em Do (agrupar as colcheias em 3 + 3)")


def d_m3_partitura_konokol():
    return _score_image("konokol", [("C", 4, None), ("E", 4, None), ("D", 4, None), ("F", 4, None),
                                    ("E", 4, None), ("G", 4, None), ("C", 5, None), ("G", 4, None)],
                        "Partitura: celula ritmica em Do para falar e tocar")


DIAGRAMS.update({
    "m3_leitura_ritmica": d_m3_leitura_ritmica,
    "m3_pulsacao_subdivisao": d_m3_pulsacao_subdivisao,
    "m3_cifrado_divisao": d_m3_cifrado_divisao,
    "m3_celulas_ritmicas": d_m3_celulas_ritmicas,
    "m3_acentuacoes": d_m3_acentuacoes,
    "m3_levadas_palheta": d_m3_levadas_palheta,
    "m3_direcoes_palheta": d_m3_direcoes_palheta,
    "m3_mapa_mao_direita": d_m3_mapa_mao_direita,
    "m3_levadas_dedos": d_m3_levadas_dedos,
    "m3_compassos": d_m3_compassos,
    "m3_formulas_incomuns": d_m3_formulas_incomuns,
    "m3_konokol": d_m3_konokol,
    "m3_percussao_sanfona": d_m3_percussao_sanfona,
    "m3_partitura_leitura": d_m3_partitura_leitura,
    "m3_partitura_subdivisao": d_m3_partitura_subdivisao,
    "m3_partitura_cifrado": d_m3_partitura_cifrado,
    "m3_partitura_celula": d_m3_partitura_celula,
    "m3_partitura_palheta": d_m3_partitura_palheta,
    "m3_partitura_dedos": d_m3_partitura_dedos,
    "m3_partitura_compasso": d_m3_partitura_compasso,
    "m3_partitura_konokol": d_m3_partitura_konokol,
})


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
