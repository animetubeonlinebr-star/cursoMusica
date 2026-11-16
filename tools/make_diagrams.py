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
SEMITONES = {"C": 0, "D": 2, "E": 4, "F": 5, "G": 7, "A": 9, "B": 11}
STAFF_LINE_GAP = 26

# Notes actually drawn on each score image, keyed by the image stem. main()
# writes them to Source/Course/Content/ScoreNotes.h so the tests can prove that
# a score image and the audio played beside it carry the same notes.
SCORE_NOTES: dict[str, list[int]] = {}


def _midi(letter: str, octave: int, accidental: str | None) -> int:
    pc = SEMITONES[letter]
    if accidental == "#":
        pc += 1
    elif accidental == "b":
        pc -= 1
    return (octave + 1) * 12 + pc


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
        # The renderer reads only letter[0] and draws the accidental only when
        # the third field is set, so a note must be spelled ("C", 4, "#") — not
        # ("C#", 4, None), which silently drops the sharp.
        if len(letter) != 1 or accidental not in (None, "#", "b"):
            raise ValueError(f"malformed note { (letter, octave, accidental) }: "
                             "use (letter, octave, '#'|'b'|None)")
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
    # `name` is the score's image stem; the notes actually drawn are recorded so
    # main() can emit a manifest (Source/Course/Content/ScoreNotes.h) that the
    # tests use to prove each score image matches the audio carried beside it.
    SCORE_NOTES[name] = [_midi(letter, octave, accidental)
                         for (letter, octave, accidental) in notes]
    h = 420
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, caption)
    staff(d, MARGIN + 30, y + 40, W - 2 * MARGIN - 60, notes)
    return img


def d_m2_partitura_terca():
    return _score_image("m2_partitura_terca", [("C", 4, None), ("E", 4, None)],
                        "Partitura: terca maior (Do-Mi)")


def d_m2_partitura_tercas():
    return _score_image("m2_partitura_tercas", [("C", 4, None), ("E", 4, None), ("C", 4, None), ("E", 4, "b")],
                        "Partitura: terca maior e terca menor (Do-Mi / Do-Mib)")


def d_m2_partitura_triade():
    return _score_image("m2_partitura_triade", [("C", 4, None), ("E", 4, None), ("G", 4, None), ("C", 5, None)],
                        "Partitura: triade de Do maior com a oitava")


def d_m2_partitura_intervalos():
    return _score_image("m2_partitura_intervalos", [("C", 4, None), ("D", 4, None), ("E", 4, None), ("F", 4, None),
                                                    ("G", 4, None), ("A", 4, None), ("B", 4, None), ("C", 5, None)],
                        "Partitura: escala de Do maior (cada passo e um intervalo)")


def d_m2_partitura_arpejo():
    return _score_image("m2_partitura_arpejo", [("C", 4, None), ("E", 4, None), ("G", 4, None), ("C", 5, None),
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
# Modulo 9 — harmonia avancada e estruturas especiais.
# --------------------------------------------------------------------------
def _rows_panel(d, y, items, row_h=56, label_w=360, font_size=21):
    top = y + 34
    for i, (name, desc, feel) in enumerate(items):
        yy = top + i * row_h
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + row_h - 8], radius=8,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 18, yy + (row_h - 8) / 2), name, font=font(font_size, True),
               fill=ACCENT, anchor="lm")
        d.text((MARGIN + label_w, yy + (row_h - 8) / 2), desc, font=font(font_size - 1),
               fill=TXT, anchor="lm")
        if feel:
            d.text((W - MARGIN - 18, yy + (row_h - 8) / 2), feel,
                   font=font(font_size - 1, True), fill=CYAN, anchor="rm")


def _cycle_ring(d, cx, cy, r_out, r_in, cells, inner, note_font=26):
    n = len(cells)
    for i, cell in enumerate(cells):
        step = 360 / n
        d.pieslice([cx - r_out, cy - r_out, cx + r_out, cy + r_out],
                   start=-90 + i * step - step / 2, end=-90 + i * step + step / 2,
                   fill=RAISED if i % 2 == 0 else SURFACE, outline=BORDER)
        am = math.radians(-90 + i * step)
        d.text((cx + (r_out - 58) * math.cos(am), cy + (r_out - 58) * math.sin(am)),
               cell, font=font(note_font, True), fill=TXT, anchor="mm")
    if inner:
        d.ellipse([cx - r_in, cy - r_in, cx + r_in, cy + r_in],
                  fill=ACCENT_MUTED, outline=BORDER, width=2)
        for k, line in enumerate(inner):
            d.text((cx, cy - 14 + k * 30), line, font=font(22, True), fill=TXT, anchor="mm")


def d_m9_diminuto_formacao():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Formacao do acorde diminuto")
    y = subtitle(d, "Terca menor + terca menor: 0-3-6 na triade; 0-3-6-9 no dim7.", y)
    groups = [("Triade diminuta", ["Do", "Mib", "Solb"], "0 - 3 - 6"),
              ("Diminuto de setima (dim7)", ["Do", "Mib", "Solb", "Sibb"], "0 - 3 - 6 - 9")]
    top = y + 50
    for g, (name, notes, formula) in enumerate(groups):
        yy = top + g * 220
        d.text((MARGIN, yy), name, font=font(24, True), fill=ACCENT, anchor="la")
        d.text((W - MARGIN, yy), formula, font=font(22, True), fill=GOLD, anchor="ra")
        for k, note in enumerate(notes):
            cx = MARGIN + 90 + k * 200
            cy = yy + 100
            d.ellipse([cx - 46, cy - 46, cx + 46, cy + 46], fill=RAISED,
                      outline=CYAN, width=3)
            d.text((cx, cy), note, font=font(24, True), fill=TXT, anchor="mm")
            if k < len(notes) - 1:
                d.text((cx + 100, cy - 30), "+ 3m", font=font(17, True), fill=TXT2, anchor="mm")
    d.text((W / 2, h - 60), "Cada terca menor sobrepoe uma casa a menos: o acorde se repete a cada 3 semitons.",
           font=font(20), fill=TXT2, anchor="mm")
    return img


def d_m9_diminuto_funcoes():
    h = 640
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Funcoes do acorde diminuto")
    y = subtitle(d, "O diminuto aparece como sensivel, como substituto de dominante e como passagem.", y)
    items = [("vii dim (sensivel)", "Conduz a tonica; nasce do 7o grau da escala maior", "dominante"),
             ("ii dim (menor)", "2o grau do campo menor; prepara o V7", "subdominante"),
             ("dim de passagem", "Liga dois acordes por graus conjuntos", "cromatismo"),
             ("dim substituto", "Dim7 sobre a 3a traz 3a, 5a, 7a e 9a do dominante", "dominante"),
             ("dim sobre pedal", "Cor e tensao sobre uma tonica sustentada", "cor")]
    _rows_panel(d, y, items)
    d.text((W / 2, h - 46), "Um dim7 tem quatro grafias enarmonicas: qualquer nota pode ser a fundamental.",
           font=font(19), fill=GOLD, anchor="mm")
    return img


def d_m9_domdim_escala():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Dominante diminuto (DomDim): escala meio-tom / tom")
    y = subtitle(d, "C7b9 = C Db Eb E F# G A Bb. As quatro dominantes 7b9 usam a mesma dim7.", y)
    scale = ["C", "Db", "Eb", "E", "F#", "G", "A", "Bb"]
    bw = (W - 2 * MARGIN) / len(scale)
    for i, note in enumerate(scale):
        cx = MARGIN + bw * (i + 0.5)
        d.rounded_rectangle([cx - 44, y + 50, cx + 44, y + 146], radius=10,
                            fill=RAISED, outline=CYAN if i % 2 == 0 else ACCENT, width=3)
        d.text((cx, y + 98), note, font=font(26, True), fill=TXT, anchor="mm")
        d.text((cx, y + 180), "m" if i % 2 == 0 else "T", font=font(18, True),
               fill=TXT2, anchor="mm")
    d.text((MARGIN, y + 230), "Os quatro dominantes a uma terca menor usam a mesma escala diminuta:",
           font=font(21, True), fill=TXT2, anchor="la")
    doms = ["C7b9", "Eb7b9", "Gb7b9", "A7b9"]
    for i, name in enumerate(doms):
        cx = MARGIN + 180 + i * 260
        d.rounded_rectangle([cx - 110, y + 270, cx + 110, y + 350], radius=10,
                            fill=ACCENT_MUTED, outline=ACCENT, width=2)
        d.text((cx, y + 310), name, font=font(26, True), fill=TXT, anchor="mm")
    d.text((W / 2, h - 60), "Trocar a fundamental entre essas quatro e uma rearmonizacao classica.",
           font=font(20), fill=GOLD, anchor="mm")
    return img


def d_m9_ciclos_diminutos():
    h = 820
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Ciclos diminutos: o circulo das tercas menores")
    y = subtitle(d, "De 3 em 3 semitons a nota volta ao inicio; so existem tres dim7 diferentes.", y)
    cx, cy = W / 2, y + 360
    _cycle_ring(d, cx, cy, 300, 210, ["C", "Eb", "Gb", "A"], ["Dim7 de", "Do / Mib /", "Solb / La"])
    d.text((MARGIN, h - 130), "Cdim7 = Ebdim7 = Gbdim7 = Adim7 (mesmas notas, outra grafia).",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 92), "Os outros dois grupos comecam em C# e em D: no total, tres dim7.",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 54), "O ciclo tambem vale para a escala diminuta e para o DomDim.",
           font=font(21, True), fill=GOLD, anchor="la")
    return img


def d_m9_campo_diminuto():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Campos harmonicos das escalas diminutas")
    y = subtitle(d, "As duas escalas de 8 notas geram campos diferentes ao empilhar tercas.", y)
    cols = [("Tom - meio - tom (0,2,3,5,6,8,9,11)",
             ["dois dim7 a um tom", "Cdim7 e Ddim7", "0-3-6-9 / 0-3-6-9"], CYAN),
            ("Meio - tom - meio (0,1,3,4,6,7,9,10)",
             ["quatro dominantes", "C7  Eb7  Gb7  A7", "cada um com 7(b9)"], ACCENT)]
    col_w = (W - 2 * MARGIN) / 2
    for c, (name, lines, color) in enumerate(cols):
        x = MARGIN + c * col_w
        d.rounded_rectangle([x + 10, y + 40, x + col_w - 10, y + 400], radius=12, fill=RAISED)
        d.text((x + col_w / 2, y + 80), name, font=font(20, True), fill=color, anchor="mm")
        for i, line in enumerate(lines):
            d.text((x + col_w / 2, y + 160 + i * 54), line, font=font(23), fill=TXT, anchor="mm")
    d.text((W / 2, h - 60), "A escala diminuta tem 8 notas e apenas 3 transposicoes distintas.",
           font=font(20), fill=TXT2, anchor="mm")
    return img


def d_m9_m7s5():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Acorde m7(#5): a quinta aumentada")
    y = subtitle(d, "0-3-8-10 (tonica, 3a menor, 5a aumentada, 7a menor).", y)
    chord_box(d, MARGIN + 200, y + 90, 200, 210, [-1, 3, 6, 3, 4, -1], "Cm7(#5)",
              start_fret=1, caption="Do - Mib - Lab - Sib")
    items = [("Cm7(#5)", "0-3-8-10", "cor e suspensao"),
             ("= Ab(add9)/C", "mesmas notas, outro nome", "enarmonia"),
             ("m7 com 5a justa", "0-3-7-10", "compare e ouça")]
    top = y + 90
    for i, (name, desc, feel) in enumerate(items):
        yy = top + i * 96
        d.rounded_rectangle([MARGIN + 480, yy, W - MARGIN, yy + 80], radius=10,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 500, yy + 20), name, font=font(22, True), fill=ACCENT, anchor="la")
        d.text((MARGIN + 500, yy + 52), desc, font=font(19), fill=TXT, anchor="la")
        d.text((W - MARGIN - 16, yy + 40), feel, font=font(19, True), fill=CYAN, anchor="rm")
    d.text((W / 2, h - 54), "A quinta aumentada deixa o acorde suspenso: nem maior, nem menor, nem dominante.",
           font=font(20), fill=GOLD, anchor="mm")
    return img


def d_m9_policordes():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Policordes: dois acordes empilhados")
    y = subtitle(d, "Escreve-se o acorde de cima sobre o de baixo; cada camada e uma triade.", y)
    upper = ["Re", "Fa#", "La"]
    lower = ["Do", "Mi", "Sol"]
    for row, (name, notes, color) in enumerate([("Triade superior", upper, CYAN),
                                                ("Triade inferior", lower, ACCENT)]):
        yy = y + 60 + row * 190
        d.text((MARGIN, yy), name, font=font(22, True), fill=color, anchor="la")
        for k, note in enumerate(notes):
            cx = MARGIN + 380 + k * 150
            cy = yy + 50
            d.ellipse([cx - 44, cy - 44, cx + 44, cy + 44], fill=RAISED, outline=color, width=3)
            d.text((cx, cy), note, font=font(24, True), fill=TXT, anchor="mm")
    d.text((W / 2, y + 330), "D sobre C  =  D/C", font=font(30, True), fill=GOLD, anchor="mm")
    d.text((MARGIN, h - 110), "O baixo (inferior) fixa a harmonia; o superior acrescenta tensao.",
           font=font(20), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 70), "Policorde = duas triades; slash chord = um acorde com nota estranha no baixo.",
           font=font(20), fill=TXT2, anchor="la")
    return img


def d_m9_simetria():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Simetria: escalas que dividem a oitava")
    y = subtitle(d, "Quando a oitava se divide em partes iguais, a escala se repete no braco.", y)
    items = [("Diminuta (8 notas)", "0-1-3-4-6-7-9-10: divide em 4 tercas menores", "3 escalas"),
             ("Tom inteiro (6 notas)", "0-2-4-6-8-10: divide em 6 tons", "2 escalas"),
             ("Aumentada (6 notas)", "0-3-4-7-8-11: tercas maiores + semitons", "4 escalas"),
             ("Pentatonica", "nao e simetrica: e uma selecao da escala", "12 escalas")]
    _rows_panel(d, y, items, row_h=62, label_w=380)
    d.text((W / 2, h - 54), "A simetria permite deslocar a digitacao sem mudar o desenho do braco.",
           font=font(20), fill=GOLD, anchor="mm")
    return img


def d_m9_relacoes_campos():
    h = 760
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Relacoes entre campos harmonicos")
    y = subtitle(d, "Campos vizinhos no circulo das quintas compartilham seis das sete notas.", y)
    cx, cy = W / 2, y + 330
    _cycle_ring(d, cx, cy, 260, 150,
                ["C", "G", "D", "A", "E", "B", "F#", "Db", "Ab", "Eb", "Bb", "F"], [])
    d.text((MARGIN, h - 150), "Um acorde comum aos dois campos e o pivo da modulacao.",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 112), "Dominantes secundarios e diminutos ligam campos distantes.",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 74), "O dim7 e o mesmo em quatro campos: e uma ponte entre eles.",
           font=font(21, True), fill=GOLD, anchor="la")
    return img


def d_m9_sonoridades():
    h = 680
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Sonoridades especiais")
    y = subtitle(d, "Estruturas que fogem do acorde terca-sobre-terca e criam cores novas.", y)
    items = [("Quartal (So What)", "empilha quartas em vez de tercas", "aberto"),
             ("Cluster", "notas vizinhas soando juntas", "denso"),
             ("Add9 / 6-9", "triade com a nona ou a sexta e a nona", "luminoso"),
             ("Slash / inversao", "acorde com nota estranha no baixo", "movel"),
             ("Upper structure", "triade sobre um dominante", "tenso")]
    _rows_panel(d, y, items, row_h=56, label_w=380)
    d.text((W / 2, h - 46), "Cada sonoridade tem um uso: cor, tensao, movimento ou repouso.",
           font=font(20), fill=GOLD, anchor="mm")
    return img


def d_m9_partitura_dim7():
    return _score_image("m9_partitura_dim7", [("C", 4, None), ("E", 4, "b"), ("G", 4, "b"),
                                              ("A", 4, None), ("C", 5, None)],
                        "Partitura: arpejo de Cdim7 (Do-Mib-Solb-La-Do)")


def d_m9_partitura_domdim():
    return _score_image("m9_partitura_domdim", [("C", 4, None), ("E", 4, None), ("G", 4, None),
                                                ("B", 4, "b"), ("D", 5, "b")],
                        "Partitura: C7(b9) - Do-Mi-Sol-Sib-Reb")


def d_m9_partitura_m7s5():
    return _score_image("m9_partitura_m7s5", [("C", 4, None), ("E", 4, "b"), ("G", 4, "#"),
                                              ("B", 4, "b"), ("C", 5, None)],
                        "Partitura: arpejo de Cm7(#5) - Do-Mib-Sol#-Sib")


def d_m9_partitura_policorde():
    return _score_image("m9_partitura_policorde", [("C", 4, None), ("E", 4, None), ("G", 4, None),
                                                   ("D", 5, None), ("F", 5, "#"), ("A", 5, None)],
                        "Partitura: policorde D/C - triade de Do (baixo) e de Re (agudo)")


DIAGRAMS.update({
    "m9_diminuto_formacao": d_m9_diminuto_formacao,
    "m9_diminuto_funcoes": d_m9_diminuto_funcoes,
    "m9_domdim_escala": d_m9_domdim_escala,
    "m9_ciclos_diminutos": d_m9_ciclos_diminutos,
    "m9_campo_diminuto": d_m9_campo_diminuto,
    "m9_m7s5": d_m9_m7s5,
    "m9_policordes": d_m9_policordes,
    "m9_simetria": d_m9_simetria,
    "m9_relacoes_campos": d_m9_relacoes_campos,
    "m9_sonoridades": d_m9_sonoridades,
    "m9_partitura_dim7": d_m9_partitura_dim7,
    "m9_partitura_domdim": d_m9_partitura_domdim,
    "m9_partitura_m7s5": d_m9_partitura_m7s5,
    "m9_partitura_policorde": d_m9_partitura_policorde,
})


def _write_score_notes_header(path: str) -> None:
    """Emit the notes drawn on each score image as a C++ header the tests read.

    Keeps the score image and the audio beside it in sync: the test compares the
    notes of a ContentItem of kind score with the ones recorded here (the same
    notes the image draws)."""
    lines = [
        "#pragma once",
        "",
        "// GENERATED by tools/make_diagrams.py - do not edit by hand.",
        "// Notes drawn on each score image, so the tests can prove a score image",
        "// and the audio played beside it carry the same notes.",
        "",
        "#include <juce_core/juce_core.h>",
        "",
        "#include <vector>",
        "",
        "namespace cursomusica::content::scoreNotes",
        "{",
        "",
        "struct Entry { const char* stem; std::vector<int> notes; };",
        "",
        "inline const std::vector<Entry>& all()",
        "{",
        "    static const std::vector<Entry> entries = {",
    ]
    for stem in sorted(SCORE_NOTES):
        notes = ", ".join(str(n) for n in SCORE_NOTES[stem])
        lines.append(f'        {{ "{stem}", {{ {notes} }} }},')
    lines += [
        "    };",
        "    return entries;",
        "}",
        "",
        "} // namespace cursomusica::content::scoreNotes",
        "",
    ]
    with open(path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))






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





# --------------------------------------------------------------------------
# Modulo 4 — construcao de acordes: triades e tetrades.
# --------------------------------------------------------------------------
def _info_rows(d, y, rows, x=MARGIN, w=None, row_h=52):
    """Lista de linhas (rotulo | texto | destaque), no estilo dos outros diagramas."""
    w = w or (W - 2 * MARGIN)
    for i, (a, b, c) in enumerate(rows):
        yy = y + i * row_h
        d.rounded_rectangle([x, yy, x + w, yy + row_h - 8], radius=8,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((x + 18, yy + (row_h - 8) / 2), a, font=font(21, True), fill=ACCENT, anchor="lm")
        d.text((x + 300, yy + (row_h - 8) / 2), b, font=font(20), fill=TXT, anchor="lm")
        if c:
            d.text((x + w - 18, yy + (row_h - 8) / 2), c, font=font(20, True), fill=CYAN, anchor="rm")
    return y + len(rows) * row_h


def d_m4_triades_maior_menor():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Triades: maior e menor")
    y = subtitle(d, "Tonica e quinta iguais; so a terca muda: 4 semitons (maior) ou 3 (menor).", y)
    chord_box(d, W / 2 - 300, y + 70, 150, 170, [-1, 3, 2, 0, 1, 0], "Do maior (C)",
              start_fret=1, caption="Do - Mi - Sol  (0, 4, 7)", note_font=font(13, True))
    chord_box(d, W / 2 + 300, y + 70, 150, 170, [-1, 3, 5, 5, 4, 3], "Do menor (Cm)",
              start_fret=3, caption="Do - Mib - Sol  (0, 3, 7)", note_font=font(13, True))
    _info_rows(d, y + 320, [
        ("Maior (0,4,7)", "terca maior define o som aberto/alegre", "C  Dm  E  F  G  Am"),
        ("Menor (0,3,7)", "terca menor define o som fechado/triste", "Cm  Dm  Em  Fm  Gm"),
        ("Regra", "mesma forma desloca a tonica; a qualidade vem da terca", "3a define o acorde"),
    ])
    return img


def d_m4_triades_aum_dim():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Triades aumentada e diminuta")
    y = subtitle(d, "A quinta se altera: aumentada sobe 1 semitom (0,4,8); diminuta desce 1 (0,3,6).", y)
    chord_box(d, W / 2 - 300, y + 70, 150, 170, [-1, 3, 2, 1, 1, 0], "Do aumentado (Caug)",
              start_fret=1, caption="Do - Mi - Sol#  (0, 4, 8)", note_font=font(12, True))
    chord_box(d, W / 2 + 300, y + 70, 150, 170, [-1, 3, 4, 5, 4, -1], "Do diminuto (Cdim)",
              start_fret=1, caption="Do - Mib - Solb  (0, 3, 6)", note_font=font(12, True))
    _info_rows(d, y + 320, [
        ("Aumentada (0,4,8)", "quinta aumentada: som suspenso, de passagem", "Caug"),
        ("Diminuta (0,3,6)", "quinta diminuta: som tenso, quase instavel", "Cdim"),
        ("Onde aparecem", "vii do campo harmonico e dominantes alteradas", "Bdim, G7(b9)"),
    ])
    return img


def d_m4_abertas_fechadas():
    h = 760
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Triades abertas e fechadas")
    y = subtitle(d, "Fechada: as notas ficam juntas, dentro de uma oitava. Aberta: as notas se espalham.", y)
    chord_box(d, W / 2 - 300, y + 60, 140, 160, [0, 3, 2, 0, 1, 0], "Fechada (C, 1a pos.)",
              start_fret=1, caption="notas vizinhas no braco", note_font=font(12, True))
    chord_box(d, W / 2 + 300, y + 60, 140, 160, [-1, -1, 2, 5, 5, 3], "Aberta (C no 2o setor)",
              start_fret=2, caption="notas separadas por cordas", note_font=font(12, True))
    _info_rows(d, y + 300, [
        ("Fechada", "notas empilhadas: som compacto, ideal p/ acompanhar", "C na 1a posicao"),
        ("Aberta", "notas espalhadas por varias cordas: som amplo", "C com cordas soltas"),
        ("Uso", "aberta brilha no violao; fechada corta na mixagem", "escolha pelo contexto"),
    ])
    return img


def d_m4_inversoes():
    braco_h = 6 * 28                 # seis cordas, com folga para as notas
    pitch = 220                      # passo entre linhas: caber rotulo + braco + folga
    h = 920
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Inversoes da triade de Do (C - E - G)")
    y = subtitle(d, "A inversao muda qual nota fica no baixo; o acorde continua sendo Do maior.", y)
    rows = [
        ("Fundamental (Do no baixo)", [-1, -1, 10, 9, 8, -1], "Do - Mi - Sol"),
        ("1a inversao (Mi no baixo)", [-1, -1, 2, 0, 1, -1], "Mi - Sol - Do"),
        ("2a inversao (Sol no baixo)", [-1, -1, 5, 5, 5, -1], "Sol - Do - Mi"),
    ]
    for k, (label, frets, cap) in enumerate(rows):
        top = y + 60 + k * pitch
        d.text((MARGIN, top), label, font=font(20, True), fill=CYAN, anchor="la")
        string_labels(d, MARGIN + 10, top + 34, braco_h, gap_font=font(13, True))
        # Pitch classes actually sounded, and the bass = lowest sounding string
        # (the first non-muted entry, since TUNING runs from the 6th to the 1st).
        sounded = {(open_midi + f) % 12 for (open_midi, _), f in zip(TUNING, frets) if f >= 0}
        bass_pc = next((open_midi + f) % 12 for (open_midi, _), f in zip(TUNING, frets) if f >= 0)
        played = [f for f in frets if f >= 0]
        start = max(0, min(played) - 1)
        n = max(5, max(played) - start + 2)
        fretboard(d, MARGIN + 40, top + 34, W - 2 * MARGIN - 80, braco_h, n_frets=n,
                  start_fret=start, highlight=sounded, root_pc=bass_pc, note_font=font(12, True))
        d.text((W - MARGIN, top + 34), cap, font=font(17, True), fill=GOLD, anchor="ra")
    d.text((W / 2, h - 74), "Roxo: nota do baixo (a que define a inversao). Ciano: as demais notas do acorde.",
           font=font(18), fill=TXT2, anchor="mm")
    d.text((W / 2, h - 40), "Mesmas notas, ordem diferente: muda a conducao de vozes.",
           font=font(20, True), fill=TXT2, anchor="mm")
    return img


def d_m4_tetrades():
    h = 760
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Tetrades: a triade mais a setima")
    y = subtitle(d, "A setima define a familia: maior (11), menor (10) ou diminuta (9) semitons acima.", y)
    boxes = [([-1, 3, 2, 0, 0, 0], "Do7M", 1, "Do-Mi-Sol-Si  (0,4,7,11)"),
             ([-1, 3, 2, 3, 1, 0], "Do7", 1, "Do-Mi-Sol-Sib  (0,4,7,10)"),
             ([8, 10, 8, 8, 8, 8], "Dom7", 8, "Do-Mib-Sol-Sib  (0,3,7,10)"),
             ([-1, 3, 4, 3, 4, -1], "Dom7(b5)", 1, "Do-Mib-Solb-Sib  (0,3,6,10)")]
    bw = (W - 2 * MARGIN) / 4
    for i, (frets, name, start, cap) in enumerate(boxes):
        chord_box(d, MARGIN + bw * (i + 0.5), y + 60, 120, 150, frets, name,
                  start_fret=start, caption=cap, note_font=font(11, True))
    _info_rows(d, y + 330, [
        ("7a maior (0,4,7,11)", "som brilhante e suspenso", "C7M, F7M"),
        ("7a dominante (0,4,7,10)", "som tenso que pede resolucao", "G7, C7"),
        ("7a menor (0,3,7,10)", "som do blues e da MPB", "Cm7, Am7"),
        ("meio-diminuto (0,3,6,10)", "usado no ii do menor", "Bm7(b5), Dm7(b5)"),
    ])
    return img


def d_m4_formacao_acordes():
    h = 740
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Formacao de acordes: intervalos empilhados sobre a tonica")
    y = subtitle(d, "O nome do acorde descreve os intervalos: tonica, terca, quinta e (na tetrade) a setima.", y)
    groups = [("Triade maior (0,4,7)", ["Do", "Mi", "Sol"], ACCENT),
              ("Triade menor (0,3,7)", ["Do", "Mib", "Sol"], CYAN),
              ("Tetrade 7a maior (0,4,7,11)", ["Do", "Mi", "Sol", "Si"], SUCCESS),
              ("Tetrade 7a dominante (0,4,7,10)", ["Do", "Mi", "Sol", "Sib"], GOLD)]
    top = y + 40
    for i, (name, notes, color) in enumerate(groups):
        yy = top + i * 118
        d.text((MARGIN, yy + 8), name, font=font(23, True), fill=color, anchor="la")
        for k, note in enumerate(notes):
            cx = MARGIN + 46 + k * 120
            cy = yy + 66
            d.ellipse([cx - 36, cy - 36, cx + 36, cy + 36], fill=RAISED, outline=color, width=3)
            d.text((cx, cy), note, font=font(22, True), fill=TXT, anchor="mm")
    d.text((W / 2, h - 44), "Empilhe tercas a partir da tonica e voce nomeia qualquer acorde.",
           font=font(20), fill=TXT2, anchor="mm")
    return img


def d_m4_caged_familias():
    h = 780
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Sistema 5 (CAGED): as cinco formas do acorde de Do maior")
    y = subtitle(d, "Cinco formas cobrem o braco inteiro e se repetem a cada 12 casas.", y)
    shapes = [([-1, 3, 2, 0, 1, 0], "C", 1, "forma de C"),
              ([-1, 3, 5, 5, 5, 3], "A", 3, "forma de A"),
              ([8, 7, 5, 5, 5, 8], "G", 5, "forma de G"),
              ([8, 10, 10, 9, 8, 8], "E", 8, "forma de E"),
              ([-1, -1, 10, 9, 8, 8], "D", 8, "forma de D")]
    bw = (W - 2 * MARGIN) / 5
    for i, (frets, name, start, cap) in enumerate(shapes):
        chord_box(d, MARGIN + bw * (i + 0.5), y + 60, 110, 150, frets, name,
                  start_fret=start, caption=cap, note_font=font(11, True))
    _info_rows(d, y + 320, [
        ("Ordem no braco", "C -> A -> G -> E -> D, subindo pelas casas", "repete na casa 12"),
        ("Familia", "cada forma serve para maior, menor e setima", "muda a qualidade"),
        ("Ligacao", "a ultima nota de uma forma e a primeira da proxima", "braco inteiro"),
    ])
    return img


def d_m4_cinco_fases():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "As cinco fases das familias de acordes")
    y = subtitle(d, "Cada familia (maior, menor, 7...) aprende-se em cinco fases, da forma a aplicacao.", y)
    rows = [("Fase 1", "reconhecer a forma no braco", "so a posicao"),
            ("Fase 2", "tocar a forma em todas as posicoes", "CAGED"),
            ("Fase 3", "mudar de acorde mantendo a forma", "conducao de vozes"),
            ("Fase 4", "aplicar em progressao (C-Am-Dm-G)", "musica real"),
            ("Fase 5", "criar/inverter livremente", "dominio")]
    _info_rows(d, y + 40, rows, row_h=76)
    d.text((W / 2, h - 44), "Fase 1 e 2: forma. Fase 3 e 4: mudanca. Fase 5: liberdade.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m4_acordes_clean():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Acordes clean: pestana e meio barre sem ruido")
    y = subtitle(d, "Corda abafada ou zumbido estraga o acorde: dedo atras do traste e polegar no meio do braco.", y)
    chord_box(d, W / 2 - 300, y + 60, 150, 170, [1, 3, 3, 2, 1, 1], "Fa maior (pestana)",
              start_fret=1, caption="6 cordas soando limpas", note_font=font(12, True))
    chord_box(d, W / 2 + 300, y + 60, 150, 170, [-1, 2, 4, 4, 3, 2], "Si menor (meio barre)",
              start_fret=2, caption="5 cordas, a 6a abafada", note_font=font(12, True))
    _info_rows(d, y + 300, [
        ("Dedo atras do traste", "o som sai limpo, sem abafamento", "limpeza"),
        ("Polegar no meio do braco", "da alavanca para a pestana", "forca"),
        ("Cordas certas", "abafe (x) as cordas que nao pertencem ao acorde", "clean"),
    ])
    return img


def d_m4_distribuicao_braco():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Distribuicao da triade de Do pelo braco")
    y = subtitle(d, "As mesmas notas (Do - Mi - Sol) reaparecem por todo o braco: escolha a regiao que encaixa.", y)
    string_labels(d, MARGIN + 10, y + 50, 6 * 46, gap_font=font(15, True))
    fretboard(d, MARGIN + 50, y + 50, W - 2 * MARGIN - 60, 6 * 46, n_frets=12,
              start_fret=0, highlight={0, 4, 7}, root_pc=0, note_font=font(12, True))
    d.text((MARGIN, h - 100), "Roxo: tonica (Do). Ciano: terca (Mi) e quinta (Sol).",
           font=font(20), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 60), "Achar a tonica primeiro: o resto da triade esta sempre a 3 e a 7 semitons.",
           font=font(20, True), fill=GOLD, anchor="la")
    return img


def d_m4_partitura_triade():
    return _score_image("m4_triade", [("C", 4, None), ("E", 4, None), ("G", 4, None), ("C", 5, None)],
                        "Partitura: triade de Do maior (Do-Mi-Sol-Do)")


def d_m4_partitura_inversao():
    return _score_image("m4_inversao", [("E", 4, None), ("G", 4, None), ("C", 5, None)],
                        "Partitura: 1a inversao (Mi-Sol-Do)")


def d_m4_partitura_tetrade():
    return _score_image("m4_tetrade", [("C", 4, None), ("E", 4, None), ("G", 4, None),
                                       ("B", 4, None), ("C", 5, None)],
                        "Partitura: tetrade de Do7M (Do-Mi-Sol-Si)")


def d_m4_partitura_familia():
    return _score_image("m4_familia", [("C", 4, None), ("E", 4, None), ("G", 4, None),
                                       ("E", 4, "b"), ("G", 4, "b")],
                        "Partitura: familia de Do (maior -> diminuta)")


def d_m4_partitura_progressao():
    return _score_image("m4_progressao", [("C", 4, None), ("A", 4, None), ("D", 4, None), ("G", 4, None)],
                        "Partitura: fundamentais da progressao C-Am-Dm-G")


DIAGRAMS.update({
    "m4_triades_maior_menor": d_m4_triades_maior_menor,
    "m4_triades_aum_dim": d_m4_triades_aum_dim,
    "m4_abertas_fechadas": d_m4_abertas_fechadas,
    "m4_inversoes": d_m4_inversoes,
    "m4_tetrades": d_m4_tetrades,
    "m4_formacao_acordes": d_m4_formacao_acordes,
    "m4_caged_familias": d_m4_caged_familias,
    "m4_cinco_fases": d_m4_cinco_fases,
    "m4_acordes_clean": d_m4_acordes_clean,
    "m4_distribuicao_braco": d_m4_distribuicao_braco,
    "m4_partitura_triade": d_m4_partitura_triade,
    "m4_partitura_inversao": d_m4_partitura_inversao,
    "m4_partitura_tetrade": d_m4_partitura_tetrade,
    "m4_partitura_familia": d_m4_partitura_familia,
    "m4_partitura_progressao": d_m4_partitura_progressao,
})





# --------------------------------------------------------------------------
# Modulo 5 — campo harmonico maior e funcoes harmonicas.
# --------------------------------------------------------------------------
def _table(d, y, headers, rows, col_x, row_h=46, header_color=ACCENT):
    """Tabela simples: `col_x` = posicoes x de cada coluna."""
    d.text((MARGIN, y), headers[0], font=font(19, True), fill=header_color, anchor="la")
    for i, head in enumerate(headers[1:], start=1):
        d.text((col_x[i], y), head, font=font(19, True), fill=header_color, anchor="la")
    for r, row in enumerate(rows):
        yy = y + 32 + r * row_h
        fill = RAISED if r % 2 == 0 else SURFACE
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + row_h - 6], radius=8, fill=fill)
        for c, cell in enumerate(row):
            color = TXT if c == 0 else TXT2
            d.text((col_x[c] if c else MARGIN + 14, yy + (row_h - 6) / 2), cell,
                   font=font(20, True if c == 0 else False), fill=color, anchor="lm")
    return y + 32 + len(rows) * row_h


def d_m5_escala_maior_graus():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "A escala maior: graus, tons e semitons")
    y = subtitle(d, "Padrao T - T - S - T - T - T - S. Os semitons ficam entre 3-4 e 7-8.", y)
    piano(d, MARGIN + 30, y + 30, W - 2 * MARGIN - 60, 230)
    steps = ["T", "T", "S", "T", "T", "T", "S"]
    kw = (W - 2 * MARGIN - 60) / 8
    for i, s in enumerate(steps):
        d.text((MARGIN + 30 + (i + 1) * kw, y + 300), s, font=font(24, True),
               fill=GOLD if s == "S" else CYAN, anchor="mm")
    notes = ["Do", "Re", "Mi", "Fa", "Sol", "La", "Si", "Do"]
    for i, n in enumerate(notes):
        d.text((MARGIN + 30 + i * kw, y + 350), n, font=font(22, True), fill=TXT, anchor="mm")
        d.text((MARGIN + 30 + i * kw, y + 386), str(i + 1), font=font(20, True),
               fill=ACCENT, anchor="mm")
    d.text((MARGIN, y + 450), "Os graus (1..8) numeram as notas da escala; a tonica e o grau 1.",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, y + 492), "O mesmo padrao vale em qualquer tonica: muda a nota, nao o desenho.",
           font=font(21, True), fill=GOLD, anchor="la")
    d.text((MARGIN, y + 534), "Graus 1, 3 e 5 formam a triade de tonica daquele tom.",
           font=font(21), fill=CYAN, anchor="la")
    return img


def d_m5_graus_romanos():
    h = 680
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Os graus em algarismo romano")
    y = subtitle(d, "Maiusculo = acorde maior; minusculo = menor; circulo = diminuto.", y)
    items = [("I", "C", "maior", ACCENT), ("ii", "Dm", "menor", CYAN),
             ("iii", "Em", "menor", CYAN), ("IV", "F", "maior", ACCENT),
             ("V", "G", "maior", ACCENT), ("vi", "Am", "menor", CYAN),
             ("vii", "Bdim", "diminuto", GOLD)]
    top = y + 40
    for i, (deg, chord, quality, color) in enumerate(items):
        yy = top + i * 66
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 56], radius=8,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 24, yy + 28), deg + ("o" if quality == "diminuto" else ""),
               font=font(24, True), fill=color, anchor="lm")
        d.text((MARGIN + 220, yy + 28), chord, font=font(22, True), fill=TXT, anchor="lm")
        d.text((MARGIN + 520, yy + 28), quality, font=font(21), fill=TXT2, anchor="lm")
        d.text((MARGIN + 820, yy + 28),
               "repouso" if deg in ("I", "iii", "vi") else
               ("afastamento" if deg in ("IV", "ii") else "tensao"),
               font=font(20, True), fill=CYAN, anchor="lm")
    return img


def d_m5_campo_harmonico_maior():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Campo harmonico maior (de Do)")
    y = subtitle(d, "I ii iii IV V vi vii - os sete acordes que nascem da escala maior.", y)
    chords = [("C", "I"), ("Dm", "ii"), ("Em", "iii"), ("F", "IV"),
              ("G", "V"), ("Am", "vi"), ("Bdim", "vii")]
    bw = (W - 2 * MARGIN) / 4
    for i, (name, deg) in enumerate(chords):
        cx = MARGIN + bw * (i % 4 + 0.5)
        cy = y + 60 + (i // 4) * 220
        d.rounded_rectangle([cx - bw / 2 + 20, cy, cx + bw / 2 - 20, cy + 150],
                            radius=12, fill=RAISED, outline=BORDER, width=2)
        d.text((cx, cy + 40), deg + ("o" if deg == "vii" else ""), font=font(30, True),
               fill=ACCENT, anchor="mm")
        d.text((cx, cy + 90), name, font=font(26, True), fill=TXT, anchor="mm")
        quality = "maior" if deg in ("I", "IV", "V") else ("menor" if deg != "vii" else "diminuto")
        d.text((cx, cy + 126), quality, font=font(19), fill=CYAN, anchor="mm")
    d.text((W / 2, h - 52), "Padrao fixo: I ii iii IV V vi vii. Vale em qualquer tonalidade.",
           font=font(21, True), fill=GOLD, anchor="mm")
    return img


def d_m5_campo_harmonico_braco():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Campo harmonico de Do no braco")
    y = subtitle(d, "Tonica (Do) em violeta, terceira em ciano, quinta em dourado.", y)
    string_labels(d, MARGIN + 30, y + 60, 6 * 58)
    fretboard(d, MARGIN + 50, y + 60, W - 2 * MARGIN - 50, 6 * 58,
              highlight={0, 4, 7}, root_pc=0)
    d.text((MARGIN, h - 116), "As tríades do campo se montam sobre as notas destacadas.",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 74), "Ache a tonica (Do) e conte os graus para achar cada acorde.",
           font=font(21, True), fill=GOLD, anchor="la")
    return img


def d_m5_funcoes_tres():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "As tres funcoes harmonicas")
    y = subtitle(d, "Tonica (repouso), subdominante (afastamento) e dominante (tensao).", y)
    cols = [("TONICA", "repouso", ["I (C)", "iii (Em)", "vi (Am)"], ACCENT, "em casa"),
            ("SUBDOMINANTE", "afastamento", ["IV (F)", "ii (Dm)"], CYAN, "sai de casa"),
            ("DOMINANTE", "tensao", ["V (G)", "V7 (G7)", "vii (Bdim)"], GOLD, "pede voltar")]
    col_w = (W - 2 * MARGIN) / 3
    for c, (name, role, chords, color, feel) in enumerate(cols):
        x = MARGIN + c * col_w
        d.rounded_rectangle([x + 12, y + 30, x + col_w - 12, y + 30 + 380],
                            radius=12, fill=RAISED, outline=color, width=3)
        d.text((x + col_w / 2, y + 70), name, font=font(26, True), fill=color, anchor="mm")
        d.text((x + col_w / 2, y + 112), role, font=font(21), fill=TXT2, anchor="mm")
        for i, ch in enumerate(chords):
            d.text((x + col_w / 2, y + 170 + i * 52), ch, font=font(23, True),
                   fill=TXT, anchor="mm")
        d.text((x + col_w / 2, y + 30 + 350), feel, font=font(20, True), fill=color, anchor="mm")
    d.text((W / 2, h - 60), "I - IV - V - I percorre as tres funcoes e volta ao repouso.",
           font=font(21, True), fill=GOLD, anchor="mm")
    return img


def d_m5_relativos():
    h = 640
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Acordes relativos: mesma armadura, cores diferentes")
    y = subtitle(d, "O relativo menor esta 3 semitons abaixo do acorde maior.", y)
    pairs = [("C", "Am", "Do e Mi em comum"), ("G", "Em", "Sol e Si em comum"),
             ("F", "Dm", "Fa e La em comum"), ("D", "Bm", "Re e Fa# em comum")]
    top = y + 40
    for i, (maj, minr, common) in enumerate(pairs):
        yy = top + i * 96
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 82], radius=10, fill=RAISED)
        d.text((MARGIN + 40, yy + 41), maj, font=font(34, True), fill=ACCENT, anchor="lm")
        d.text((MARGIN + 180, yy + 41), "<->", font=font(26, True), fill=TXT_DIS, anchor="lm")
        d.text((MARGIN + 320, yy + 41), minr, font=font(34, True), fill=CYAN, anchor="lm")
        d.text((MARGIN + 560, yy + 41), common, font=font(21), fill=TXT2, anchor="lm")
    d.text((W / 2, h - 56), "Duas das tres notas sao iguais: por isso a troca soa suave.",
           font=font(21, True), fill=GOLD, anchor="mm")
    return img


def d_m5_relativos_campo():
    h = 620
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Pares de relativos no campo de Do")
    y = subtitle(d, "Cada acorde maior do campo tem o seu relativo menor dois graus depois.", y)
    pairs = [("I", "C", "vi", "Am"), ("IV", "F", "ii", "Dm"), ("V", "G", "iii", "Em")]
    top = y + 60
    for i, (d1, c1, d2, c2) in enumerate(pairs):
        yy = top + i * 130
        d.rounded_rectangle([MARGIN + 60, yy, W - MARGIN - 60, yy + 104], radius=12,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 160, yy + 52), f"{d1} {c1}", font=font(28, True), fill=ACCENT, anchor="mm")
        d.text((W / 2, yy + 52), "<->", font=font(26, True), fill=TXT_DIS, anchor="mm")
        d.text((W - MARGIN - 160, yy + 52), f"{d2} {c2}", font=font(28, True), fill=CYAN, anchor="mm")
    d.text((W / 2, h - 56), "Trocar um acorde pelo seu relativo muda a cor sem mudar a funcao.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m5_ciclo_quintas():
    h = 900
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Ciclo das quintas: sustenidos e bemois")
    y = subtitle(d, "Subir de quinta acrescenta um sustenido; descer, um bemol.", y)
    cx, cy = W / 2, y + 380
    r_out, r_in = 300, 210
    majors = ["C", "G", "D", "A", "E", "B", "F#", "C#", "Ab", "Eb", "Bb", "F"]
    accs = ["0", "1#", "2#", "3#", "4#", "5#", "6#", "7#", "4b", "3b", "2b", "1b"]
    for i in range(12):
        d.pieslice([cx - r_out, cy - r_out, cx + r_out, cy + r_out],
                   start=-90 + i * 30 - 15, end=-90 + i * 30 + 15,
                   fill=RAISED if i % 2 == 0 else SURFACE, outline=BORDER)
        am = math.radians(-90 + i * 30)
        d.text((cx + (r_out - 52) * math.cos(am), cy + (r_out - 52) * math.sin(am)),
               majors[i], font=font(26, True), fill=TXT, anchor="mm")
        d.text((cx + (r_in - 46) * math.cos(am), cy + (r_in - 46) * math.sin(am)),
               accs[i], font=font(17), fill=CYAN, anchor="mm")
    d.ellipse([cx - 120, cy - 120, cx + 120, cy + 120], fill=ACCENT_MUTED, outline=BORDER, width=2)
    d.text((cx, cy - 14), "CICLO DAS", font=font(22, True), fill=TXT, anchor="mm")
    d.text((cx, cy + 18), "QUINTAS", font=font(22, True), fill=TXT, anchor="mm")
    d.text((MARGIN, h - 100), "Anel externo: tonalidade maior.  Anel interno: numero de acidentes.",
           font=font(20), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 62), "Sentido horario (quintas) = sustenidos; anti-horario (quartas) = bemois.",
           font=font(20, True), fill=GOLD, anchor="la")
    return img


def d_m5_cadencias():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "As principais cadencias")
    y = subtitle(d, "Cada cadencia tem um efeito: conclusao, suavidade, suspensao ou surpresa.", y)
    items = [("Autentica", "V - I", "conclusao forte (ponto final)", ACCENT),
             ("Plagal", "IV - I", "conclusao suave (amen)", CYAN),
             ("Meia cadencia", "I - V", "suspensao (virgula)", GOLD),
             ("De engano", "V - vi", "surpresa (adia a conclusao)", DANGER)]
    top = y + 50
    for i, (name, degrees, effect, color) in enumerate(items):
        yy = top + i * 110
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 92], radius=10,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 30, yy + 30), name, font=font(26, True), fill=color, anchor="la")
        d.text((MARGIN + 30, yy + 66), degrees, font=font(22), fill=TXT, anchor="la")
        d.text((MARGIN + 460, yy + 46), effect, font=font(21), fill=TXT2, anchor="lm")
    d.text((W / 2, h - 56), "As cadencias sao a pontuacao da frase musical.",
           font=font(21, True), fill=GOLD, anchor="mm")
    return img


def d_m5_progressao_padrao():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Progressao I - IV - V - I no braco")
    y = subtitle(d, "Cada acorde do campo aparece na sua regiao, com a funcao marcada.", y)
    steps = [("I", "C", "tonica", [0, 3, 2, 0, 1, 0], 1),
             ("IV", "F", "subdominante", [1, 3, 3, 2, 1, 1], 1),
             ("V", "G", "dominante", [3, 2, 0, 0, 0, 3], 1),
             ("I", "C", "tonica", [0, 3, 2, 0, 1, 0], 1)]
    bw = (W - 2 * MARGIN) / 4
    for i, (deg, name, func, frets, start) in enumerate(steps):
        cx = MARGIN + bw * (i + 0.5)
        chord_box(d, cx, y + 70, 150, 170, frets, f"{name} ({deg})", start_fret=start,
                  caption=func, note_font=font(12, True))
    d.text((W / 2, h - 56), "Repouso - afastamento - tensao - repouso: o ciclo completo.",
           font=font(21, True), fill=GOLD, anchor="mm")
    return img


def d_m5_modos_escala():
    h = 760
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Os sete modos da escala maior")
    y = subtitle(d, "As mesmas notas de Do maior, cada modo comecando em um grau diferente.", y)
    modes = [("I", "Jonio", "Do", "maior"), ("II", "Dorico", "Re", "menor com brilho"),
             ("III", "Frigio", "Mi", "sombrio"), ("IV", "Lidio", "Fa", "brilhante"),
             ("V", "Mixolidio", "Sol", "maior com blues"), ("VI", "Eolio", "La", "menor natural"),
             ("VII", "Locrio", "Si", "instavel")]
    top = y + 30
    for i, (deg, name, start, feel) in enumerate(modes):
        yy = top + i * 84
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 70], radius=8,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 24, yy + 35), deg, font=font(22, True), fill=ACCENT, anchor="lm")
        d.text((MARGIN + 130, yy + 35), name, font=font(24, True), fill=TXT, anchor="lm")
        d.text((MARGIN + 440, yy + 35), f"comeca em {start}", font=font(20), fill=CYAN, anchor="lm")
        d.text((MARGIN + 720, yy + 35), feel, font=font(20, True), fill=GOLD, anchor="lm")
    return img


def d_m5_harmonizacao():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Harmonizando a escala maior")
    y = subtitle(d, "Sobre cada grau, empilha-se 1 - 3 - 5 (as notas da propria escala).", y)
    rows = [("1 - 3 - 5", "Do - Mi - Sol", "C", "maior"),
            ("2 - 4 - 6", "Re - Fa - La", "Dm", "menor"),
            ("3 - 5 - 7", "Mi - Sol - Si", "Em", "menor"),
            ("4 - 6 - 8", "Fa - La - Do", "F", "maior"),
            ("5 - 7 - 9", "Sol - Si - Re", "G", "maior"),
            ("6 - 8 - 10", "La - Do - Mi", "Am", "menor"),
            ("7 - 9 - 11", "Si - Re - Fa", "Bdim", "diminuto")]
    col_x = [0, MARGIN + 260, MARGIN + 560, MARGIN + 780]
    _table(d, y + 30, ["Empilhamento", "Notas", "Acorde", "Qualidade"], rows, col_x, row_h=54)
    d.text((W / 2, h - 52), "O empilhamento de tercas transforma a escala em campo harmonico.",
           font=font(21, True), fill=GOLD, anchor="mm")
    return img


def d_m5_harmonizacao_braco():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Escala harmonizada no braco (Do maior)")
    y = subtitle(d, "As notas da escala de Do maior nas 12 primeiras casas.", y)
    string_labels(d, MARGIN + 30, y + 60, 6 * 58)
    fretboard(d, MARGIN + 50, y + 60, W - 2 * MARGIN - 50, 6 * 58,
              highlight={0, 2, 4, 5, 7, 9, 11}, root_pc=0)
    d.text((MARGIN, h - 116), "Tonica (Do) em violeta; as demais notas da escala em ciano.",
           font=font(21), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 74), "Sobre cada tonica, monte a triade (1-3-5) para harmonizar.",
           font=font(21, True), fill=GOLD, anchor="la")
    return img


def _score_image_m5(caption, notes):
    h = 420
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, caption)
    staff(d, MARGIN + 30, y + 40, W - 2 * MARGIN - 60, notes)
    return img


def d_m5_partitura_escala():
    return _score_image_m5("Partitura: escala de Do maior",
                           [("C", 4, None), ("D", 4, None), ("E", 4, None), ("F", 4, None),
                            ("G", 4, None), ("A", 4, None), ("B", 4, None), ("C", 5, None)])


def d_m5_partitura_campo():
    return _score_image_m5("Partitura: campo harmonico de Do (C - Dm - Em)",
                           [("C", 4, None), ("E", 4, None), ("G", 4, None),
                            ("D", 4, None), ("F", 4, None), ("A", 4, None),
                            ("E", 4, None), ("G", 4, None), ("B", 4, None)])


def d_m5_partitura_triade_tonica():
    return _score_image_m5("Partitura: triade de tonica (Do maior)",
                           [("C", 4, None), ("E", 4, None), ("G", 4, None)])


def d_m5_partitura_iv_v_i():
    return _score_image_m5("Partitura: IV - V - I em Do (F - G - C)",
                           [("F", 4, None), ("A", 4, None), ("C", 5, None),
                            ("G", 4, None), ("B", 4, None), ("D", 5, None),
                            ("C", 5, None), ("E", 5, None), ("G", 5, None)])


def d_m5_partitura_relativos():
    return _score_image_m5("Partitura: vi - IV - V - vi (Am - F - G - Am)",
                           [("A", 3, None), ("C", 4, None), ("E", 4, None),
                            ("F", 4, None), ("A", 4, None), ("C", 5, None),
                            ("G", 4, None), ("B", 4, None), ("D", 5, None),
                            ("A", 3, None), ("C", 4, None), ("E", 4, None)])


def d_m5_partitura_cadencia():
    return _score_image_m5("Partitura: cadencia autentica I - V - I (C - G - C)",
                           [("C", 4, None), ("E", 4, None), ("G", 4, None),
                            ("G", 4, None), ("B", 4, None), ("D", 5, None),
                            ("C", 5, None), ("E", 5, None), ("G", 5, None)])


def d_m5_partitura_modo():
    return _score_image_m5("Partitura: modo dorico (as notas de Do maior a partir de Re)",
                           [("D", 4, None), ("E", 4, None), ("F", 4, None), ("G", 4, None),
                            ("A", 4, None), ("B", 4, None), ("C", 5, None), ("D", 5, None)])


DIAGRAMS.update({
    "m5_escala_maior_graus": d_m5_escala_maior_graus,
    "m5_graus_romanos": d_m5_graus_romanos,
    "m5_campo_harmonico_maior": d_m5_campo_harmonico_maior,
    "m5_campo_harmonico_braco": d_m5_campo_harmonico_braco,
    "m5_funcoes_tres": d_m5_funcoes_tres,
    "m5_relativos": d_m5_relativos,
    "m5_relativos_campo": d_m5_relativos_campo,
    "m5_ciclo_quintas": d_m5_ciclo_quintas,
    "m5_cadencias": d_m5_cadencias,
    "m5_progressao_padrao": d_m5_progressao_padrao,
    "m5_modos_escala": d_m5_modos_escala,
    "m5_harmonizacao": d_m5_harmonizacao,
    "m5_harmonizacao_braco": d_m5_harmonizacao_braco,
    "m5_partitura_escala": d_m5_partitura_escala,
    "m5_partitura_campo": d_m5_partitura_campo,
    "m5_partitura_triade_tonica": d_m5_partitura_triade_tonica,
    "m5_partitura_iv_v_i": d_m5_partitura_iv_v_i,
    "m5_partitura_relativos": d_m5_partitura_relativos,
    "m5_partitura_cadencia": d_m5_partitura_cadencia,
    "m5_partitura_modo": d_m5_partitura_modo,
})





# --------------------------------------------------------------------------
# Modulo 6 — escalas menores e campos harmonicos.
# --------------------------------------------------------------------------
def _m6_scale_image(title_text, subtitle_text, pcs, root_pc, footnote):
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, title_text)
    y = subtitle(d, subtitle_text, y)
    fretboard(d, MARGIN + 44, y + 40, W - 2 * MARGIN - 88, 300,
              n_frets=12, start_fret=0, show_notes=True, highlight=pcs, root_pc=root_pc)
    string_labels(d, MARGIN + 12, y + 40, 300)
    d.text((MARGIN, h - 118), "Roxo: tonica. Ciano: notas da escala. Cada corda e uma regua de semitons.",
           font=font(20), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 74), footnote, font=font(21, True), fill=GOLD, anchor="la")
    return img


def d_m6_escala_menor_natural():
    return _m6_scale_image(
        "Escala menor natural (La menor)",
        "Graus: 1  2  b3  4  5  b6  b7. Em La menor: A B C D E F G.",
        {9, 11, 0, 2, 4, 5, 7}, 9,
        "Menor natural = relativa maior comecando no 6o grau (La menor = Do maior).")


def d_m6_menor_harmonica():
    return _m6_scale_image(
        "Escala menor harmonica (La menor harmonica)",
        "Graus: 1  2  b3  4  5  b6  7. Em La menor harmonica: A B C D E F G#.",
        {9, 11, 0, 2, 4, 5, 8}, 9,
        "O 7o grau sobe (G#): cria a sensivel e o intervalo de 2a aumentada (F -> G#).")


def d_m6_menor_melodica():
    return _m6_scale_image(
        "Escala menor melodica (La menor melodica)",
        "Graus: 1  2  b3  4  5  6  7. Em La menor melodica: A B C D E F# G#.",
        {9, 11, 0, 2, 4, 6, 8}, 9,
        "Sobem o 6o e o 7o graus (F# e G#): sobe suave e resolve a sensivel sem o salto.")


def d_m6_campo_harmonico_menor():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Campo harmonico menor de La (menor natural)")
    y = subtitle(d, "i  ii  III  iv  v  VI  VII — os acordes que nascem da escala.", y)
    chords = [("Am", "i", "tonica", [-1, 0, 2, 2, 1, 0]),
              ("Bm7b5", "ii", "subdominante", [-1, 2, 3, 2, 3, -1]),
              ("Cmaj7", "III", "relativa maior", [-1, 3, 2, 0, 0, 0]),
              ("Dm7", "iv", "subdominante", [-1, -1, 0, 2, 1, 1]),
              ("Em7", "v", "dominante fraco", [0, 2, 2, 0, 3, 0]),
              ("Fmaj7", "VI", "subdominante", [-1, -1, 3, 2, 1, 0]),
              ("G7", "VII", "dominante", [3, 2, 0, 0, 0, 1])]
    bw = (W - 2 * MARGIN) / 4
    for i, (name, deg, func, frets) in enumerate(chords):
        cx = MARGIN + bw * (i % 4 + 0.5)
        cy = y + 70 + (i // 4) * 300
        chord_box(d, cx, cy, 130, 140, frets, f"{name} ({deg})", start_fret=1,
                  caption=func, note_font=font(12, True))
    return img


def _m6_modes_image(title_text, subtitle_text, items, footnote):
    h = 120 + len(items) * 62
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, title_text)
    y = subtitle(d, subtitle_text, y)
    top = y + 34
    for i, (name, degrees, color) in enumerate(items):
        yy = top + i * 62
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 52], radius=8,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 18, yy + 26), name, font=font(22, True), fill=color, anchor="lm")
        d.text((MARGIN + 420, yy + 26), degrees, font=font(20), fill=TXT, anchor="lm")
    d.text((W / 2, h - 40), footnote, font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m6_modos_harmonica():
    items = [("1. Menor harmonica", "1  2  b3  4  5  b6  7", ACCENT),
             ("2. Locrio 6 natural", "1  b2  b3  4  b5  6  b7", CYAN),
             ("3. Jonio #5", "1  2  3  4  #5  6  7", CYAN),
             ("4. Dorico #4", "1  2  b3  #4  5  6  b7", CYAN),
             ("5. Frigio dominante", "1  b2  3  4  5  b6  b7", GOLD),
             ("6. Lidio #2", "1  #2  3  #4  5  6  7", CYAN),
             ("7. Superlocrio bb7", "1  b2  b3  b4  b5  b6  bb7", DANGER)]
    return _m6_modes_image(
        "Modos da escala menor harmonica",
        "Cada modo comeca num grau diferente da mesma escala de La menor harmonica.",
        items, "O 5o modo (frigio dominante) e a sonoridade do flamenco e do V7(b9).")


def d_m6_modos_melodica():
    items = [("1. Menor melodica", "1  2  b3  4  5  6  7", ACCENT),
             ("2. Dorico b2", "1  b2  b3  4  5  6  b7", CYAN),
             ("3. Lidio aumentado", "1  2  3  #4  #5  6  7", CYAN),
             ("4. Lidio dominante", "1  2  3  #4  5  6  b7", GOLD),
             ("5. Mixolidio b6", "1  2  3  4  5  b6  b7", CYAN),
             ("6. Locrio 2 natural", "1  2  b3  4  b5  b6  b7", CYAN),
             ("7. Escala alterada", "1  b2  b3  b4  b5  b6  b7", DANGER)]
    return _m6_modes_image(
        "Modos da escala menor melodica",
        "A menor melodica gera sete sonoridades, muito usadas no jazz e na bossa.",
        items, "O 4o (lidio dominante) e o 7o (alterada) sao os mais usados sobre dominantes.")


def d_m6_relacao_maior_menor():
    h = 560
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Maior, menor relativa e menor paralela")
    y = subtitle(d, "Tres escalas com a mesma tonica ou a mesma armadura — e sons bem diferentes.", y)
    cols = [("Do maior", ["C  Dm  Em  F  G  Am  Bdim"], "1 2 3 4 5 6 7", ACCENT),
            ("La menor (relativa)", ["Am  Bdim  C  Dm  Em  F  G"], "1 2 b3 4 5 b6 b7", CYAN),
            ("Do menor (paralela)", ["Cm  Ddim  Eb  Fm  Gm  Ab  Bb"], "1 2 b3 4 5 b6 b7", GOLD)]
    top = y + 50
    col_w = (W - 2 * MARGIN) / 3
    for c, (name, field, degrees, color) in enumerate(cols):
        x = MARGIN + c * col_w
        d.rounded_rectangle([x + 12, top, x + col_w - 12, top + 330], radius=12, fill=RAISED)
        d.text((x + col_w / 2, top + 34), name, font=font(24, True), fill=color, anchor="mm")
        d.text((x + col_w / 2, top + 92), field[0], font=font(19, True), fill=TXT, anchor="mm")
        d.text((x + col_w / 2, top + 150), degrees, font=font(19), fill=TXT2, anchor="mm")
        d.text((x + col_w / 2, top + 230), "mesma tonica" if c != 1 else "mesma armadura",
               font=font(18), fill=CYAN, anchor="mm")
    d.text((W / 2, h - 46), "Relativa: mesma armadura, outra tonica. Paralela: mesma tonica, outra armadura.",
           font=font(20), fill=GOLD, anchor="mm")
    return img


def d_m6_subdominante_menor():
    h = 660
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Subdominantes menores emprestados (em Do maior)")
    y = subtitle(d, "Acordes do campo menor paralelo usados dentro do campo maior.", y)
    items = [("iv — Fm7", "empresta o b6 (Ab) e o b3 (Eb)", "menor"),
             ("ii — Dm7(b5)", "subdominante menor meio-diminuto", "instavel"),
             ("bVI — Abmaj7", "cor de MPB e bossa", "suave"),
             ("bVII — Bb7", "dominante do bIII", "modal"),
             ("bIII — Eb", "relativa do campo menor", "escura"),
             ("bII — Db (napolitano)", "bII maior, cadencia dramatica", "dramatico")]
    top = y + 40
    for i, (name, role, feel) in enumerate(items):
        yy = top + i * 62
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 52], radius=8,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 18, yy + 26), name, font=font(22, True), fill=ACCENT, anchor="lm")
        d.text((MARGIN + 470, yy + 26), role, font=font(20), fill=TXT, anchor="lm")
        d.text((MARGIN + 1020, yy + 26), feel, font=font(20, True), fill=CYAN, anchor="lm")
    return img


def d_m6_modos_gregos():
    items = [("Jonio (maior)", "1  2  3  4  5  6  7", ACCENT),
             ("Dorico", "1  2  b3  4  5  6  b7", CYAN),
             ("Frigio", "1  b2  b3  4  5  b6  b7", CYAN),
             ("Lidio", "1  2  3  #4  5  6  7", CYAN),
             ("Mixolidio", "1  2  3  4  5  6  b7", CYAN),
             ("Eolio (menor natural)", "1  2  b3  4  5  b6  b7", ACCENT),
             ("Locrio", "1  b2  b3  4  b5  b6  b7", DANGER)]
    return _m6_modes_image(
        "Os sete modos gregos (a partir da escala maior)",
        "Cada modo e a escala maior comecando num grau diferente.",
        items, "Tres sao maiores (jonio, lidio, mixolidio), tres menores (dorico, frigio, eolio) e um diminuto.")


def d_m6_partitura_menor_natural():
    return _score_image("menor natural", [("A", 3, None), ("B", 3, None), ("C", 4, None),
                                          ("D", 4, None), ("E", 4, None), ("F", 4, None),
                                          ("G", 4, None), ("A", 4, None)],
                        "Partitura: escala de La menor natural (A B C D E F G A)")


def d_m6_partitura_menor_harmonica():
    return _score_image("menor harmonica", [("A", 3, None), ("B", 3, None), ("C", 4, None),
                                            ("D", 4, None), ("E", 4, None), ("F", 4, None),
                                            ("G", 4, "#"), ("A", 4, None)],
                        "Partitura: escala de La menor harmonica (G# como sensivel)")


def d_m6_partitura_menor_melodica():
    return _score_image("menor melodica", [("A", 3, None), ("B", 3, None), ("C", 4, None),
                                           ("D", 4, None), ("E", 4, None), ("F", 4, "#"),
                                           ("G", 4, "#"), ("A", 4, None)],
                        "Partitura: escala de La menor melodica (F# e G#)")


def d_m6_partitura_campo_menor():
    return _score_image("campo menor", [("A", 3, None), ("C", 4, None), ("E", 4, None),
                                        ("D", 4, None), ("F", 4, None), ("A", 4, None),
                                        ("E", 4, None), ("G", 4, "#"), ("B", 4, None),
                                        ("A", 3, None), ("C", 4, None), ("E", 4, None)],
                        "Partitura: i - iv - V - i em La menor (Am / Dm / E7 / Am)")


def d_m6_partitura_subdominante():
    return _score_image("subdominante", [("C", 4, None), ("E", 4, None), ("G", 4, None),
                                         ("B", 4, None), ("F", 4, None), ("A", 4, "b"),
                                         ("C", 5, None), ("E", 5, "b"),
                                         ("C", 4, None), ("E", 4, None), ("G", 4, None),
                                         ("B", 4, None)],
                        "Partitura: I - iv - I em Do (C7M / Fm7 / C7M)")


def d_m6_partitura_dorico():
    return _score_image("dorico", [("D", 4, None), ("E", 4, None), ("F", 4, None),
                                   ("G", 4, None), ("A", 4, None), ("B", 4, None),
                                   ("C", 5, None), ("D", 5, None)],
                        "Partitura: escala de Re dorico (D E F G A B C D)")


def d_m6_partitura_gregos():
    return _score_image("modos gregos", [("C", 4, None), ("D", 4, None), ("E", 4, None),
                                         ("F", 4, None), ("G", 4, None), ("A", 4, None),
                                         ("B", 4, None), ("C", 5, None)],
                        "Partitura: Do jonio (= escala de Do maior) — base dos modos")


DIAGRAMS.update({
    "m6_escala_menor_natural": d_m6_escala_menor_natural,
    "m6_menor_harmonica": d_m6_menor_harmonica,
    "m6_menor_melodica": d_m6_menor_melodica,
    "m6_modos_harmonica": d_m6_modos_harmonica,
    "m6_modos_melodica": d_m6_modos_melodica,
    "m6_campo_harmonico_menor": d_m6_campo_harmonico_menor,
    "m6_subdominante_menor": d_m6_subdominante_menor,
    "m6_relacao_maior_menor": d_m6_relacao_maior_menor,
    "m6_modos_gregos": d_m6_modos_gregos,
    "m6_partitura_menor_natural": d_m6_partitura_menor_natural,
    "m6_partitura_menor_harmonica": d_m6_partitura_menor_harmonica,
    "m6_partitura_menor_melodica": d_m6_partitura_menor_melodica,
    "m6_partitura_campo_menor": d_m6_partitura_campo_menor,
    "m6_partitura_subdominante": d_m6_partitura_subdominante,
    "m6_partitura_dorico": d_m6_partitura_dorico,
    "m6_partitura_gregos": d_m6_partitura_gregos,
})





# --------------------------------------------------------------------------
# Modulo 7 — Empilhamentos, estruturas modais e sonoridades.
# --------------------------------------------------------------------------
def _stack_rows(d, top, groups, note_font=None):
    """Desenha grupos de notas empilhadas; `groups` = [(rotulo, [notas], cor)]."""
    note_font = note_font or font(24, True)
    for i, (name, notes, color) in enumerate(groups):
        yy = top + i * 118
        d.text((MARGIN, yy + 10), name, font=font(23, True), fill=color, anchor="la")
        for k, note in enumerate(notes):
            cx = MARGIN + 60 + k * 128
            cy = yy + 72
            d.ellipse([cx - 38, cy - 38, cx + 38, cy + 38], fill=RAISED, outline=color, width=3)
            d.text((cx, cy), note, font=note_font, fill=TXT, anchor="mm")


def d_m7_tercas_empilhadas():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Empilhamento de tercas")
    y = subtitle(d, "Cada nota nova comeca onde a anterior terminou; a mistura de tercas define a qualidade.", y)
    _stack_rows(d, y + 40, [
        ("Triade maior 1-3-5 (0,4,7)", ["Do", "Mi", "Sol"], ACCENT),
        ("Tetrade 7M 1-3-5-7 (0,4,7,11)", ["Do", "Mi", "Sol", "Si"], SUCCESS),
        ("Dominante 1-3-5-b7 (0,4,7,10)", ["Do", "Mi", "Sol", "Sib"], GOLD),
        ("Menor 1-b3-5-b7 (0,3,7,10)", ["Do", "Mib", "Sol", "Sib"], CYAN),
    ])
    d.text((W / 2, h - 40), "As tercas empilhadas definem maior, menor e dominante.",
           font=font(20), fill=TXT2, anchor="mm")
    return img


def d_m7_quartais_empilhadas():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Empilhamento de quartas (som de So What)")
    y = subtitle(d, "Quartas justas sobrepostas; sem terca, o acorde e suspenso (nem maior, nem menor).", y)
    _stack_rows(d, y + 40, [
        ("Duas quartas: Do-Fa-Sib (0,5,10)", ["Do", "Fa", "Sib"], CYAN),
        ("Tres quartas: Do-Fa-Sib-Mib (0,5,10,15)", ["Do", "Fa", "Sib", "Mib"], ACCENT),
        ("So What: quartas + terca no topo (Sol)", ["Do", "Fa", "Sib", "Mib", "Sol"], GOLD),
    ])
    d.text((W / 2, h - 60), "O acorde quartal nao tem cara de maior nem de menor: ele suspende.",
           font=font(20), fill=TXT2, anchor="mm")
    d.text((W / 2, h - 34), "Mova o mesmo desenho pelo braco para qualquer centro modal.",
           font=font(19, True), fill=GOLD, anchor="mm")
    return img


def d_m7_outros_empilhamentos():
    h = 760
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Outros empilhamentos: quintas, segundas e mistos")
    y = subtitle(d, "Cada distancia entre as notas produz uma cor diferente.", y)
    _stack_rows(d, y + 34, [
        ("Quintas: Do-Sol-Re-La (forte, aberto)", ["Do", "Sol", "Re", "La"], ACCENT),
        ("Segundas: Do-Re-Mi (aglomerado, tenso)", ["Do", "Re", "Mi"], GOLD),
        ("Misto (quarta + terca): Do-Fa-La", ["Do", "Fa", "La"], CYAN),
    ])
    d.text((W / 2, h - 40), "Quintas dao forca; segundas dao tensao; mistos dao cor sob medida.",
           font=font(20), fill=TXT2, anchor="mm")
    return img


def d_m7_triades_do_meio():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Triades do meio sobre Do")
    y = subtitle(d, "Cada triade interna colore o acorde de base sem mudar o centro.", y)
    rows = [("Sol maior (Sol-Si-Re)", "5, 7, 9", "Do com nona"),
            ("La menor (La-Do-Mi)", "13, 1, 3", "Do com sexta"),
            ("Re menor (Re-Fa-La)", "9, 11, 13", "Do com nona e 11"),
            ("Fa maior (Fa-La-Do)", "11, 13, 1", "Do com 11")]
    top = y + 40
    for i, (triade, graus, cor) in enumerate(rows):
        yy = top + i * 92
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 78], radius=10,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 20, yy + 22), triade, font=font(24, True), fill=ACCENT, anchor="la")
        d.text((MARGIN + 20, yy + 52), "graus acrescentados: " + graus, font=font(18), fill=TXT2, anchor="la")
        d.text((W - MARGIN - 20, yy + 38), cor, font=font(22, True), fill=CYAN, anchor="ra")
    d.text((W / 2, h - 36), "Afirme o centro no baixo e use a triade do meio para colorir.",
           font=font(20), fill=TXT2, anchor="mm")
    return img


def d_m7_familias_modais():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Familias modais por acorde")
    y = subtitle(d, "Cada acorde carrega um leque de modos; escolha a cor pela intencao.", y)
    rows = [("Maior (Xmaj7)", "jonio, lidio", ACCENT),
            ("Maior #11 (Xmaj7#11)", "lidio", ACCENT),
            ("Menor (Xm7)", "dorico, eolio", CYAN),
            ("Menor b5 (Xm7b5)", "locrio", GOLD),
            ("Dominante (X7)", "mixolidio, lidio dominante, alterado", GOLD),
            ("Sus (X7sus4)", "mixolidio sus", SUCCESS)]
    top = y + 36
    for i, (acorde, modos, color) in enumerate(rows):
        yy = top + i * 88
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 74], radius=10,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 20, yy + 20), acorde, font=font(23, True), fill=color, anchor="la")
        d.text((MARGIN + 20, yy + 50), modos, font=font(19), fill=TXT, anchor="la")
    d.text((W / 2, h - 34), "A setima do acorde restringe as opcoes; as tensoes definem a cor.",
           font=font(19), fill=TXT2, anchor="mm")
    return img


def d_m7_caged_modos():
    h = 760
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "O CAGED como mapa dos modos (escala de Do)")
    y = subtitle(d, "As cinco formas cobrem o braco; cada modo e a escala vista de um grau.", y)
    fretboard(d, MARGIN + 40, y + 40, W - 2 * MARGIN - 80, 300,
              n_frets=12, start_fret=0, show_notes=True,
              highlight={0, 2, 4, 5, 7, 9, 11}, root_pc=0)
    string_labels(d, MARGIN + 10, y + 40, 300)
    d.text((MARGIN, h - 120), "Destaques: as notas da escala de Do maior (tonica em roxo).",
           font=font(20), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 84), "A ancora da frase (o grau onde voce comeca e termina) define o modo.",
           font=font(20, True), fill=GOLD, anchor="la")
    d.text((MARGIN, h - 48), "Jonion na tonica; dorico na 2a; frigio na 3a; lidio na 4a; mixolidio na 5a.",
           font=font(19), fill=CYAN, anchor="la")
    return img


def d_m7_modos_tres():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Dorico, Lidio e Mixolidio")
    y = subtitle(d, "A mesma escala maior vista de tres graus: cada ancora, uma cor.", y)
    rows = [("Dorico (menor, 6a maior)", "1 2 b3 4 5 6 b7", "aberto, jazz", CYAN),
            ("Lidio (maior, #4)", "1 2 3 #4 5 6 7", "brilhante, flutuante", ACCENT),
            ("Mixolidio (maior, b7)", "1 2 3 4 5 6 b7", "dominante, blues", GOLD)]
    top = y + 50
    for i, (nome, formula, cor, color) in enumerate(rows):
        yy = top + i * 160
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 140], radius=12, fill=RAISED)
        d.text((MARGIN + 24, yy + 24), nome, font=font(26, True), fill=color, anchor="la")
        d.text((MARGIN + 24, yy + 70), formula, font=font(30, True), fill=TXT, anchor="la")
        d.text((MARGIN + 24, yy + 108), "som: " + cor, font=font(20), fill=TXT2, anchor="la")
    return img


def d_m7_modos_sus_alt():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Variacoes do dominante: sus e #4")
    y = subtitle(d, "Uma nota alterada muda a cor do acorde dominante.", y)
    rows = [("Mixolidio natural (X7)", "1 2 3 4 5 6 b7", "terca presente", GOLD),
            ("Mixolidio sus (X7sus4)", "1 2 4 5 6 b7", "terca -> quarta", CYAN),
            ("Mixolidio #4 (X7#11)", "1 2 3 #4 5 6 b7", "quarta -> #4", ACCENT)]
    top = y + 50
    for i, (nome, formula, nota, color) in enumerate(rows):
        yy = top + i * 160
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 140], radius=12, fill=RAISED)
        d.text((MARGIN + 24, yy + 24), nome, font=font(26, True), fill=color, anchor="la")
        d.text((MARGIN + 24, yy + 70), formula, font=font(30, True), fill=TXT, anchor="la")
        d.text((MARGIN + 24, yy + 108), "o que muda: " + nota, font=font(20), fill=TXT2, anchor="la")
    return img


def d_m7_locrio_alterado():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Locrio 9 e Alterado (Alt.7)")
    y = subtitle(d, "As duas escalas de tensao do modulo: uma estavel, outra no limite.", y)
    rows = [("Locrio 9 (Xm7b5)", "1 2 b3 4 b5 b6 b7", "tensao moderada", CYAN),
            ("Alterado (X7alt)", "1 b9 #9 3 b5 #5 b7", "tensao maxima", GOLD)]
    top = y + 60
    for i, (nome, formula, tensao, color) in enumerate(rows):
        yy = top + i * 200
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 170], radius=12, fill=RAISED)
        d.text((MARGIN + 24, yy + 26), nome, font=font(28, True), fill=color, anchor="la")
        d.text((MARGIN + 24, yy + 80), formula, font=font(32, True), fill=TXT, anchor="la")
        d.text((MARGIN + 24, yy + 130), "tensao: " + tensao, font=font(21), fill=TXT2, anchor="la")
    d.text((W / 2, h - 44), "O alterado resolve meio-tom abaixo; a tensao existe para resolver.",
           font=font(20), fill=GOLD, anchor="mm")
    return img


def d_m7_aplicacoes_rock():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Aplicacoes modais no rock e no pop-rock")
    y = subtitle(d, "Cada modo, um tipo de vamp e uma cor.", y)
    rows = [("Dorico", "Xm7", "rock menor com energia", CYAN),
            ("Frigio", "Xm7 (b2)", "metal, som espanhol", GOLD),
            ("Lidio", "Xmaj7#11", "prog, passagens etéreas", ACCENT),
            ("Mixolidio", "X7", "rock, blues-rock, vamps", GOLD),
            ("Eolio", "Xm7", "rock/metal menores", CYAN),
            ("Locrio 9", "Xm7b5", "II grau de II-V-I menor", SUCCESS)]
    top = y + 34
    for i, (modo, acorde, uso, color) in enumerate(rows):
        yy = top + i * 84
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 70], radius=10,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 20, yy + 22), modo, font=font(24, True), fill=color, anchor="la")
        d.text((MARGIN + 320, yy + 24), acorde, font=font(21, True), fill=TXT, anchor="la")
        d.text((MARGIN + 620, yy + 24), uso, font=font(20), fill=TXT2, anchor="la")
    return img


def d_m7_partitura_tercas():
    return _score_image("tercas", [("C", 4, None), ("E", 4, None), ("G", 4, None), ("B", 4, None)],
                        "Partitura: Cmaj7 (empilhamento de tercas)")


def d_m7_partitura_quartal():
    return _score_image("quartal", [("C", 4, None), ("F", 4, None), ("B", 4, "b"), ("E", 5, "b"), ("G", 5, None)],
                        "Partitura: acorde quartal (estilo So What)")


def d_m7_partitura_outros():
    return _score_image("outros", [("C", 3, None), ("G", 3, None), ("D", 4, None), ("A", 4, None)],
                        "Partitura: empilhamento de quintas")


def d_m7_partitura_triade_meio():
    return _score_image("triade_meio", [("C", 3, None), ("G", 3, None), ("B", 3, None), ("D", 4, None)],
                        "Partitura: Do com a triade de Sol por cima (Cmaj9)")


def d_m7_partitura_familias():
    return _score_image("familias", [("D", 3, None), ("F", 3, None), ("A", 3, None), ("C", 4, None), ("E", 4, None)],
                        "Partitura: Dm9 (dorico)")


def d_m7_partitura_caged():
    return _score_image("caged", [("C", 4, None), ("D", 4, None), ("E", 4, None), ("F", 4, None),
                                  ("G", 4, None), ("A", 4, None), ("B", 4, None), ("C", 5, None)],
                        "Partitura: escala de Do maior (base dos modos)")


def d_m7_partitura_dorico():
    return _score_image("dorico", [("C", 4, None), ("D", 4, None), ("E", 4, "b"), ("F", 4, None),
                                   ("G", 4, None), ("A", 4, None), ("B", 4, "b"), ("C", 5, None)],
                        "Partitura: escala dorica em Do")


def d_m7_partitura_sus():
    return _score_image("sus", [("C", 4, None), ("F", 4, None), ("G", 4, None), ("B", 4, "b")],
                        "Partitura: acorde sus de Do (C7sus4)")


def d_m7_partitura_alterado():
    return _score_image("alterado", [("C", 4, None), ("D", 4, "b"), ("D", 4, "#"), ("E", 4, None),
                                     ("G", 4, "b"), ("A", 4, "b"), ("B", 4, "b")],
                        "Partitura: escala alterada em Do (Alt.7)")


def d_m7_partitura_vamp_modal():
    return _score_image("vamp_modal", [("C", 4, None), ("D", 4, None), ("E", 4, "b"), ("F", 4, None),
                                       ("G", 4, None), ("A", 4, None), ("B", 4, "b"), ("C", 5, None)],
                        "Partitura: vamp modal em Do dorico")


DIAGRAMS.update({
    "m7_tercas_empilhadas": d_m7_tercas_empilhadas,
    "m7_quartais_empilhadas": d_m7_quartais_empilhadas,
    "m7_outros_empilhamentos": d_m7_outros_empilhamentos,
    "m7_triades_do_meio": d_m7_triades_do_meio,
    "m7_familias_modais": d_m7_familias_modais,
    "m7_caged_modos": d_m7_caged_modos,
    "m7_modos_tres": d_m7_modos_tres,
    "m7_modos_sus_alt": d_m7_modos_sus_alt,
    "m7_locrio_alterado": d_m7_locrio_alterado,
    "m7_aplicacoes_rock": d_m7_aplicacoes_rock,
    "m7_partitura_tercas": d_m7_partitura_tercas,
    "m7_partitura_quartal": d_m7_partitura_quartal,
    "m7_partitura_outros": d_m7_partitura_outros,
    "m7_partitura_triade_meio": d_m7_partitura_triade_meio,
    "m7_partitura_familias": d_m7_partitura_familias,
    "m7_partitura_caged": d_m7_partitura_caged,
    "m7_partitura_dorico": d_m7_partitura_dorico,
    "m7_partitura_sus": d_m7_partitura_sus,
    "m7_partitura_alterado": d_m7_partitura_alterado,
    "m7_partitura_vamp_modal": d_m7_partitura_vamp_modal,
})





# --------------------------------------------------------------------------
# Modulo 8 — dominantes, cadencias e substituicoes harmonicas.
# --------------------------------------------------------------------------
def rows_box(d, top, rows, height=52, gap=8, cols=(0, 300, 640, 900),
             colors=(ACCENT, TXT, CYAN, GOLD), font_size=20):
    """Lista de linhas de texto alinhadas em colunas."""
    for i, row in enumerate(rows):
        yy = top + i * (height + gap)
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + height], radius=8,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        for k, cell in enumerate(row):
            if k >= len(cols) or not cell:
                continue
            d.text((MARGIN + cols[k] + 16, yy + height / 2), cell,
                   font=font(font_size, k == 0), fill=colors[k % len(colors)],
                   anchor="lm")
    return top + len(rows) * (height + gap)


def d_m8_dominante_v7():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "O dominante V7 e a sua tensao")
    y = subtitle(d, "O V7 traz a terca e a setima em tritono; elas resolvem por semitom.", y)
    # Acorde G7 em destaque + notas.
    chord_box(d, W / 2, y + 90, 320, 240, [-1, -1, -1, 0, 0, 3], "G7 (V7 de Do)",
              start_fret=1, caption="3a = Si, 7a = Fa: o tritono pede resolucao")
    notes = [("G", "tonica", "5a da escala"),
             ("B", "terca maior", "sensivel de Do"),
             ("D", "quinta justa", "estavel"),
             ("F", "setima menor", "resolves para Mi")]
    top = y + 400
    for i, (n, role, res) in enumerate(notes):
        yy = top + i * 58
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 50], radius=8,
                            fill=RAISED if i % 2 == 0 else SURFACE)
        d.text((MARGIN + 18, yy + 25), n, font=font(24, True), fill=ACCENT, anchor="lm")
        d.text((MARGIN + 120, yy + 25), role, font=font(21), fill=TXT, anchor="lm")
        d.text((MARGIN + 460, yy + 25), res, font=font(20, True), fill=CYAN, anchor="lm")
    d.text((W / 2, h - 40), "Fa (7a) desce para Mi; Si (3a) sobe para Do: resolucao V7 -> I.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m8_dominantes_secundarios():
    h = 680
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Dominantes secundarios em Do maior")
    y = subtitle(d, "Qualquer grau vira tonica temporaria com o seu proprio V7.", y)
    rows = [("V7/ii", "A7", "-> Dm", "La-Do#-Mi-Sol"),
            ("V7/iii", "B7", "-> Em", "Si-Re#-Fa#-La"),
            ("V7/IV", "C7", "-> F", "Do-Mi-Sol-Sib"),
            ("V7/V", "D7", "-> G", "Re-Fa#-La-Do"),
            ("V7/vi", "E7", "-> Am", "Mi-Sol#-Si-Re")]
    rows_box(d, y + 40, rows, cols=(0, 180, 480, 720))
    d.text((W / 2, h - 46), "O acidente (sustenido/bemol) cria a sensivel do novo alvo.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m8_dominantes_alterados():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Dominantes alterados sobre G7")
    y = subtitle(d, "A alteracao acrescenta tensao e aponta o caminho para Do.", y)
    rows = [("G7b9", "Ab na ponta", "tensao forte sobre o V"),
            ("G7#9", "A# (Bb)", "som de blues, 'acorde hendrix'"),
            ("G7b5", "Db", "substitui a 5a justa"),
            ("G7#5", "D# (Eb)", "5a aumentada, som suspenso"),
            ("G7#11", "C#", "cor lidia dominante"),
            ("G7alt", "todas juntas", "maxima tensao antes do I")]
    rows_box(d, y + 40, rows, height=56)
    d.text((W / 2, h - 44), "Quanto mais alteracoes, mais o ouvido espera a resolucao.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m8_subv7():
    h = 680
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "SubV7: o dominante substituto")
    y = subtitle(d, "Db7 toma o lugar de G7: o mesmo tritono, o baixo desce meio-tom.", y)
    left = W / 2 - 300
    chord_box(d, left, y + 90, 300, 230, [-1, -1, -1, 1, 2, 1], "G7",
              start_fret=1, caption="G-B-D-F (tritono B-F)")
    chord_box(d, W / 2 + 300, y + 90, 300, 230, [-1, -1, -1, 4, 2, 1], "Db7",
              start_fret=1, caption="Db-F-Ab-Cb (tritono F-Cb=B)")
    d.text((W / 2, y + 150), "=", font=font(48, True), fill=GOLD, anchor="mm")
    rows = [("G7", "5a -> 1a: baixo sobe (G -> C)", "resolucao forte"),
            ("Db7", "5a -> 1a: baixo desce (Db -> C)", "cromatismo"),
            ("Tritono comum", "B (=Cb) e F nos dois acordes", "ligacao")]
    rows_box(d, y + 360, rows, cols=(0, 300, 720))
    d.text((W / 2, h - 44), "SubV7 entra em qualquer lugar onde caberia o V7 do alvo.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m8_subiim():
    h = 660
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "SubIIm: o segundo grau menor")
    y = subtitle(d, "O ii vira meio-diminuto (Dm7b5) e empresta a cor do menor.", y)
    rows = [("IIm7 (normal)", "Dm7 -> G7 -> C", "Do maior puro"),
            ("SubIIm", "Dm7b5 -> G7(b9) -> C", "cor menor no ii"),
            ("iv menor", "Fm7 (emprestado)", "SubIIm na subdominante"),
            ("Efeito", "G7 ganha b9 (Ab)", "tensao extra")]
    rows_box(d, y + 50, rows, height=58)
    d.text((W / 2, h - 44), "SubIIm = o ii do campo menor, usado dentro do maior.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m8_emprestimos_modais():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Emprestimos modais: acordes do Do menor no Do maior")
    y = subtitle(d, "O modo paralelo (mesma tonica, outra qualidade) doa acordes.", y)
    rows = [("Cm", "i menor", "Do menor paralelo"),
            ("Fm7", "iv menor", "subdominante menor"),
            ("Gm7", "v menor", "dominante enfraquecido"),
            ("Ab7M", "bVI", "cor dramatica"),
            ("Bb7", "bVII", "cadencia mixolidia"),
            ("Eb7M", "bIII", "brilho modal")]
    rows_box(d, y + 40, rows, height=56)
    d.text((W / 2, h - 44), "Emprestimo modal = pegar acorde do campo paralelo emprestado.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m8_dilatacao_maior():
    h = 760
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Dilatacao do campo harmonico maior")
    y = subtitle(d, "Do campo de 7 acordes para as 12 funcoes com dominantes e emprestimos.", y)
    # Circulo de quintas simplificado com as funcoes.
    center = (W / 2, y + 240)
    radius = 190
    names = ["I", "V7/V", "V7", "V7/vi", "V7/ii", "SubV7", "SubIIm", "bVII", "ivm"]
    for i, name in enumerate(names):
        ang = -math.pi / 2 + i * (2 * math.pi / len(names))
        cx = center[0] + radius * math.cos(ang)
        cy = center[1] + radius * math.sin(ang)
        color = ACCENT if i == 0 else CYAN
        d.ellipse([cx - 44, cy - 44, cx + 44, cy + 44], fill=RAISED, outline=color, width=3)
        d.text((cx, cy), name, font=font(18, True), fill=TXT, anchor="mm")
    d.text((center[0], center[1]), "Do", font=font(40, True), fill=GOLD, anchor="mm")
    d.text((W / 2, h - 50), "Tudo gira em torno do I: os dominantes apontam para ele ou para um grau proximo.",
           font=font(20), fill=TXT2, anchor="mm")
    return img


def d_m8_dilatacao_menor():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Dilatacao do campo harmonico menor")
    y = subtitle(d, "Do menor natural ao harmonico: o V7 volta a existir e resolve em i.", y)
    rows = [("im7", "Cm7", "tonica menor"),
            ("iim7b5", "Dm7b5", "ii do menor"),
            ("bIII7M", "Eb7M", "relativo maior"),
            ("ivm7", "Fm7", "subdominante menor"),
            ("V7", "G7", "dominante (menor harmonico)"),
            ("bVI7M", "Ab7M", "cor dramatica"),
            ("bVII7", "Bb7", "dominante do bIII")]
    rows_box(d, y + 40, rows, height=54)
    d.text((W / 2, h - 44), "O V7 e o emprestimo do menor harmonico: cria a sensivel (Si) no menor.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m8_alteracoes_tensao():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Da tensao simples a maxima tensao")
    y = subtitle(d, "Cada nota alterada acrescenta tensao e aponta a resolucao.", y)
    # Escada de tensao: do dominante simples ao alterado.
    steps = [("G7", "G-B-D-F", "tensao basica"),
             ("G7b9", "G-B-D-F-Ab", "nona menor"),
             ("G7b9#11", "G-B-D-F-Ab-C#", "quarta aumentada"),
             ("G7alt", "G-B-D#-F-Ab", "todas juntas")]
    for i, (name, notes, desc) in enumerate(steps):
        yy = y + 60 + i * 110
        width = 300 + i * 130
        d.rounded_rectangle([MARGIN, yy, MARGIN + width, yy + 88], radius=10,
                            fill=RAISED, outline=ACCENT if i == len(steps) - 1 else CYAN, width=3)
        d.text((MARGIN + 24, yy + 44), name, font=font(28, True), fill=GOLD, anchor="lm")
        d.text((MARGIN + 180, yy + 44), notes, font=font(22), fill=TXT, anchor="lm")
        d.text((MARGIN + width + 24, yy + 44), desc, font=font(20), fill=TXT2, anchor="lm")
    d.text((W / 2, h - 40), "Quanto mais alto na escada, mais o ouvido espera a resolucao.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m8_ii_v_i_substituicoes():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "O II-V-I e as suas substituicoes")
    y = subtitle(d, "O mesmo alvo alcancado por caminhos diferentes.", y)
    rows = [("Tradicional", "Dm7 -> G7 -> CM7", "baixo sobe em quartas"),
            ("Com SubV7", "Dm7 -> Db7 -> CM7", "baixo desce em semitons"),
            ("Com SubIIm", "Dm7b5 -> G7b9 -> CM7", "cor do menor no ii"),
            ("Com os dois", "Dm7b5 -> Db7 -> CM7", "cromatismo total")]
    rows_box(d, y + 50, rows, height=70, cols=(0, 200, 560, 900))
    d.text((W / 2, h - 44), "O alvo nao muda: muda o caminho ate ele.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m8_ii_v_i():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "II-V-I maior e menor")
    y = subtitle(d, "O voice leading guia: a 7a de um acorde desce para a 3a do proximo.", y)
    rows = [("Maior", "Dm7 - G7 - CM7", "F->F->E, C->B->B", "resolucao luminosa"),
            ("Menor", "Dm7b5 - G7 - Cm7", "F->F->Eb, Ab->G->G", "resolucao sombria"),
            ("Menor (b9)", "Dm7b5 - G7b9 - Cm7", "Ab como b9 de G7", "tensao do menor")]
    rows_box(d, y + 50, rows, height=70, cols=(0, 160, 560, 900))
    # Mini pauta com a resolucao.
    staff(d, MARGIN + 40, y + 340, W - 2 * MARGIN - 80,
          [("D", 4, None), ("F", 4, None), ("G", 4, None), ("B", 4, None),
           ("C", 5, None), ("E", 5, None)],
          caption="Dm7 -> G7 -> CM7: a setima desce meio-tom para a terca seguinte")
    return img


def d_m8_nao_ii_v_i():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Quando NAO e um II-V-I")
    y = subtitle(d, "Nem toda tensao que resolve e um ii-V-I: reconheca o alvo real.", y)
    rows = [("Cadencia deceptiva", "G7 -> Am", "resolve no vi, nao no I"),
            ("Cadencia de backdoor", "Fm7 - Bb7 -> CM7", "ivm7 e bVII7, sem ii-V"),
            ("Dominante sem resolucao", "G7 -> F", "nao vai para o I"),
            ("Vamp modal", "Dm7 - G7 (e volta)", "falta o I: nao fecha"),
            ("II-V-I de verdade", "Dm7 - G7 - CM7", "ii -> V -> I, alvo claro")]
    rows_box(d, y + 40, rows, height=60)
    d.text((W / 2, h - 44), "Pergunte sempre: qual e o alvo e como ele e alcancado?",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m8_partitura_v7():
    return _score_image("v7", [("G", 4, None), ("B", 4, None), ("D", 5, None), ("F", 5, None)],
                        "Partitura: arpejo de G7 (V7 de Do)")


def d_m8_partitura_alterado():
    return _score_image("alterado", [("G", 4, None), ("B", 4, None), ("D", 4, "b"), ("F", 4, None),
                                     ("A", 4, "b")],
                        "Partitura: G7b5(b9) alterado resolvendo")


def d_m8_partitura_subv7():
    return _score_image("subv7", [("D", 4, "b"), ("F", 4, None), ("A", 4, "b"), ("C", 5, "b")],
                        "Partitura: arpejo de Db7 (SubV7 de Do)")


def d_m8_partitura_ii_v_i():
    return _score_image("ii_v_i", [("D", 4, None), ("F", 4, None), ("A", 4, None), ("C", 5, None),
                                   ("G", 4, None), ("B", 4, None), ("D", 5, None), ("F", 5, None),
                                   ("C", 5, None), ("E", 5, None), ("G", 5, None)],
                        "Partitura: II-V-I maior (Dm7 - G7 - CM7)")


def d_m8_partitura_ii_v_i_menor():
    return _score_image("ii_v_i_menor",
                        [("D", 4, None), ("F", 4, None), ("A", 4, "b"), ("C", 5, None),
                         ("G", 4, None), ("B", 4, None), ("D", 5, None), ("F", 5, None),
                         ("C", 5, None), ("E", 5, "b"), ("G", 5, None)],
                        "Partitura: II-V-I menor (Dm7b5 - G7 - Cm7)")


def d_m8_partitura_v7_do_v():
    return _score_image("v7_do_v", [("D", 4, None), ("F", 4, "#"), ("A", 4, None), ("C", 5, None)],
                        "Partitura: arpejo de D7 (V7/V de Do)")


def d_m8_partitura_iv_menor():
    return _score_image("iv_menor",
                        [("F", 3, None), ("A", 3, None), ("C", 4, None), ("E", 4, None),
                         ("F", 3, None), ("A", 3, "b"), ("C", 4, None), ("E", 4, "b"),
                         ("C", 3, None), ("E", 3, None), ("G", 3, None)],
                        "Partitura: FM7 - Fm7 - C (iv menor emprestado)")


DIAGRAMS.update({
    "m8_dominante_v7": d_m8_dominante_v7,
    "m8_dominantes_secundarios": d_m8_dominantes_secundarios,
    "m8_dominantes_alterados": d_m8_dominantes_alterados,
    "m8_alteracoes_tensao": d_m8_alteracoes_tensao,
    "m8_subv7": d_m8_subv7,
    "m8_subiim": d_m8_subiim,
    "m8_emprestimos_modais": d_m8_emprestimos_modais,
    "m8_dilatacao_maior": d_m8_dilatacao_maior,
    "m8_dilatacao_menor": d_m8_dilatacao_menor,
    "m8_ii_v_i": d_m8_ii_v_i,
    "m8_ii_v_i_substituicoes": d_m8_ii_v_i_substituicoes,
    "m8_nao_ii_v_i": d_m8_nao_ii_v_i,
    "m8_partitura_v7": d_m8_partitura_v7,
    "m8_partitura_alterado": d_m8_partitura_alterado,
    "m8_partitura_subv7": d_m8_partitura_subv7,
    "m8_partitura_ii_v_i": d_m8_partitura_ii_v_i,
    "m8_partitura_ii_v_i_menor": d_m8_partitura_ii_v_i_menor,
    "m8_partitura_v7_do_v": d_m8_partitura_v7_do_v,
    "m8_partitura_iv_menor": d_m8_partitura_iv_menor,
})





# --------------------------------------------------------------------------
# Modulo 10 — analise harmonica, verticalizacao e reharmonizacao.
# --------------------------------------------------------------------------
def _m10_table(d, y, headers, rows, col_x, row_h=52, title_color=ACCENT):
    d.text((col_x[0], y), headers[0], font=font(19, True), fill=title_color, anchor="la")
    for i, head in enumerate(headers[1:], start=1):
        d.text((col_x[i], y), head, font=font(19, True), fill=title_color, anchor="la")
    for r, row in enumerate(rows):
        yy = y + 30 + r * row_h
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + row_h - 8], radius=8,
                            fill=RAISED if r % 2 == 0 else SURFACE)
        for c, cell in enumerate(row):
            color = CYAN if c == 0 else TXT
            d.text((col_x[c], yy + (row_h - 8) / 2), cell, font=font(20, True if c == 0 else False),
                   fill=color, anchor="lm")
    return y + 30 + len(rows) * row_h


def d_m10_analise_harmonica():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Analise harmonica: grau, funcao e escala de cada acorde")
    y = subtitle(d, "Primeiro nomeie o grau (I, vi, ii, V); depois a funcao; depois a escala do improviso.", y)
    _m10_table(
        d, y + 30,
        ["Acorde", "Grau", "Funcao", "Escala / cor"],
        [["C7M", "I", "tonica", "jonio (modo I)"],
         ["A7", "VI7", "dominante secundario", "mixolidio alterado"],
         ["Dm7", "ii", "subdominante", "dorico"],
         ["G7", "V", "dominante", "mixolidio"]],
        col_x=[MARGIN + 18, MARGIN + 260, MARGIN + 420, MARGIN + 760])
    d.text((MARGIN, h - 92), "Todo acorde diz tres coisas: de onde vem (grau), o que faz (funcao) e como soa (escala).",
           font=font(20), fill=TXT2, anchor="la")
    d.text((MARGIN, h - 54), "O ciclo ii-V-I em Do: Dm7 -> G7 -> C7M. A analise revela o caminho antes de tocar.",
           font=font(20, True), fill=GOLD, anchor="la")
    return img


def d_m10_analise_melodica():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Analise melodica: notas do acorde x notas de tensao")
    y = subtitle(d, "Sobre Dm7, cada nota da melodia tem um papel: repouso (acorde) ou tensao (passagem).", y)
    notes = [("D", "fundamental", "repouso", SUCCESS), ("F", "3a menor", "repouso", SUCCESS),
             ("A", "5a justa", "repouso", SUCCESS), ("C", "7a menor", "repouso", SUCCESS),
             ("E", "9a", "tensao", GOLD), ("B", "13a", "tensao", GOLD),
             ("G", "11a", "tensao (evitar)", DANGER)]
    top = y + 40
    for i, (note, role, feel, color) in enumerate(notes):
        yy = top + i * 62
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 52], radius=8, fill=RAISED)
        d.ellipse([MARGIN + 30, yy + 10, MARGIN + 72, yy + 42], fill=color)
        d.text((MARGIN + 51, yy + 26), note, font=font(22, True), fill=BG, anchor="mm")
        d.text((MARGIN + 110, yy + 26), role, font=font(21, True), fill=TXT, anchor="lm")
        d.text((MARGIN + 620, yy + 26), feel, font=font(20), fill=color, anchor="lm")
    d.text((W / 2, h - 50), "Repouso cai no tempo forte; tensao pede resolucao no proximo acorde.",
           font=font(20, True), fill=CYAN, anchor="mm")
    return img


def d_m10_escolha_modal():
    h = 780
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Escolha modal: qual modo sobre cada acorde")
    y = subtitle(d, "O modo nao vem da escala da musica: vem do acorde que esta soando naquele compasso.", y)
    rows = [["Cm7 (dorico)", "menor, 6a maior", "jazz modal, funk"],
            ["Cm7 (eolio)", "menor, 6a menor", "menor natural"],
            ["Cmaj7 (jonio)", "maior, 7a maior", "tonica classica"],
            ["Cmaj7 (lidio)", "maior, 4a aumentada", "brilho flutuante"],
            ["C7 (mixolidio)", "maior, 7a menor", "dominante, blues"],
            ["C7 (lidio b7)", "maior, #11", "dominante flutuante"],
            ["Cm7b5 (locrio)", "menor, 5a dim.", "II do menor"]]
    _m10_table(d, y + 30, ["Acorde / modo", "Cor caracteristica", "Uso tipico"], rows,
               col_x=[MARGIN + 18, MARGIN + 480, MARGIN + 880], row_h=58)
    return img


def d_m10_verticalizacao():
    h = 660
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Verticalizacao: transformar melodia em harmonia")
    y = subtitle(d, "Pegue cada nota da melodia e empilhe intervalos a partir dela para criar o acorde.", y)
    melody = ["A", "G", "F", "E"]
    top = y + 60
    d.text((MARGIN, top - 10), "Melodia:", font=font(22, True), fill=ACCENT, anchor="la")
    for i, note in enumerate(melody):
        cx = MARGIN + 200 + i * 150
        d.ellipse([cx - 34, top - 44, cx + 34, top + 24], fill=ACCENT)
        d.text((cx, top - 10), note, font=font(26, True), fill=TXT, anchor="mm")
    stacks = [("Am7", ["A", "C", "E", "G"]), ("G7", ["G", "B", "D", "F"]),
              ("F7M", ["F", "A", "C", "E"]), ("Em7", ["E", "G", "B", "D"])]
    for i, (chord, notes) in enumerate(stacks):
        cx = MARGIN + 200 + i * 150
        d.text((cx, top + 70), chord, font=font(22, True), fill=CYAN, anchor="mm")
        for k, n in enumerate(notes):
            d.text((cx, top + 110 + k * 34), n, font=font(20), fill=TXT2, anchor="mm")
    d.text((W / 2, h - 56), "A melodia A-G-F-E vira Am7 - G7 - F7M - Em7: a harmonia nasce das proprias notas.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m10_conexao_campos():
    h = 700
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Conexao entre campos harmonicos (acordes-pivo)")
    y = subtitle(d, "Dois centros se ligam por acordes que existem nos dois campos: os acordes-pivo.", y)
    left = [("C7M", "I"), ("Am7", "vi"), ("Dm7", "ii"), ("G7", "V")]
    right = [("F7M", "I"), ("Dm7", "vi"), ("Gm7", "ii"), ("C7", "V")]
    cx = W / 2
    d.text((MARGIN + 120, y + 30), "Campo de Do", font=font(24, True), fill=ACCENT, anchor="mm")
    d.text((W - MARGIN - 120, y + 30), "Campo de Fa", font=font(24, True), fill=CYAN, anchor="mm")
    for i in range(4):
        yy = y + 90 + i * 100
        d.rounded_rectangle([MARGIN + 30, yy, MARGIN + 250, yy + 66], radius=10, fill=RAISED)
        d.text((MARGIN + 140, yy + 33), left[i][0] + " (" + left[i][1] + ")",
               font=font(22, True), fill=TXT, anchor="mm")
        d.rounded_rectangle([W - MARGIN - 250, yy, W - MARGIN - 30, yy + 66], radius=10, fill=RAISED)
        d.text((W - MARGIN - 140, yy + 33), right[i][0] + " (" + right[i][1] + ")",
               font=font(22, True), fill=TXT, anchor="mm")
    for i, j, label in [(2, 0, "Dm7 = vi de Fa"), (3, 3, "G7 -> C7 (V-V)")]:
        yy = y + 90 + i * 100 + 33
        y2 = y + 90 + j * 100 + 33
        d.line([MARGIN + 260, yy, W - MARGIN - 260, y2], fill=GOLD, width=3)
        d.text((cx, (yy + y2) / 2 - 14), label, font=font(19, True), fill=GOLD, anchor="mm")
    d.text((W / 2, h - 52), "Dm7 e o pivo: ii de Do, vi de Fa. Ele muda de funcao sem mudar de acorde.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m10_vozes_internas():
    h = 640
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Vozes internas: conduzir cada linha com o menor movimento")
    y = subtitle(d, "Quatro vozes (soprano, contralto, tenor, baixo) andando por graus proximos.", y)
    chords = [("C7M", ["E", "G", "B", "C"]), ("Am7", ["E", "A", "C", "A"]),
              ("Dm7", ["F", "A", "C", "D"]), ("G7", ["F", "G", "B", "D"])]
    top = y + 70
    labels = ["Soprano", "Contralto", "Tenor", "Baixo"]
    for v in range(4):
        d.text((MARGIN, top + v * 60), labels[v], font=font(19, True), fill=ACCENT, anchor="la")
    for i, (chord, voices) in enumerate(chords):
        cx = MARGIN + 340 + i * 210
        d.text((cx, top - 34), chord, font=font(23, True), fill=CYAN, anchor="mm")
        for v, note in enumerate(voices):
            d.rounded_rectangle([cx - 40, top + v * 60 - 22, cx + 40, top + v * 60 + 22],
                                radius=8, fill=RAISED, outline=BORDER)
            d.text((cx, top + v * 60), note, font=font(22, True), fill=TXT, anchor="mm")
    d.text((W / 2, h - 56), "O F comum a Dm7 e G7 fica parado: e a nota que amarra os dois acordes.",
           font=font(20, True), fill=GOLD, anchor="mm")
    return img


def d_m10_reharmonizacao():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Reharmonizar: trocar o acorde sem trocar a melodia")
    y = subtitle(d, "Para cada acorde original existem caminhos: substituto, emprestimo modal, dominante extra.", y)
    rows = [["G7", "Db7 (SubV)", "troca o baixo, mesma resolucao"],
            ["G7", "Bm7b5 - E7 (ii-V do ii)", "adiciona movimento antes de C"],
            ["C7M", "Cm6 / Cm7 (emprestimo)", "escurece a tonica"],
            ["C7M", "E7 - Am7 (relativa)", "desvia para o menor"],
            ["Dm7", "F7M (relativo maior)", "troca a cor, mantem o F"]]
    _m10_table(d, y + 30, ["Original", "Alternativa", "Efeito"], rows,
               col_x=[MARGIN + 18, MARGIN + 300, MARGIN + 700], row_h=58)
    return img


def d_m10_harmonia_alvo():
    h = 640
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Harmonia-alvo: a chegada que a melodia pede")
    y = subtitle(d, "Antes de escolher os acordes, defina onde a frase quer chegar (o alvo) e trabalhe de tras para frente.", y)
    steps = [("1. Melodia", "toque e cante a frase, sem harmonia"),
             ("2. Alvo", "defina o acorde da chegada (o repouso)"),
             ("3. Aproximacao", "escolha como chegar: ii-V, SubV, dominante"),
             ("4. Confirma", "toque a melodia sobre a nova harmonia e escute")]
    top = y + 50
    for i, (t, desc) in enumerate(steps):
        yy = top + i * 92
        d.rounded_rectangle([MARGIN, yy, W - MARGIN, yy + 76], radius=10, fill=RAISED)
        d.text((MARGIN + 24, yy + 22), t, font=font(26, True), fill=ACCENT, anchor="la")
        d.text((MARGIN + 340, yy + 26), desc, font=font(21), fill=TXT, anchor="la")
        if i < len(steps) - 1:
            d.text((W / 2, yy + 80), "v", font=font(24, True), fill=TXT_DIS, anchor="mm")
    return img


def d_m10_ferramentas():
    h = 760
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Ferramentas de reharmonizacao")
    y = subtitle(d, "Um conjunto pequeno de recursos cobre quase toda reharmonizacao.", y)
    rows = [["Substituicao de tritono", "Db7 por G7", "cromatismo no baixo"],
            ["Dominante secundario", "A7 antes de Dm7", "cria V do ii"],
            ["Emprestimo modal", "Cm7 no campo de Do", "cor do modo menor"],
            ["Relativo / paralelo", "Am7 por C7M", "mesma familia de notas"],
            ["Acorde de passagem", "Bm7b5 entre C e Dm", "movimento por graus"],
            ["Reharmonizacao melodica", "acorde a partir da nota", "verticalizacao"]]
    _m10_table(d, y + 30, ["Ferramenta", "Exemplo", "Efeito"], rows,
               col_x=[MARGIN + 18, MARGIN + 520, MARGIN + 860], row_h=58)
    return img


def d_m10_estilos():
    h = 720
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, "Estilos e sonoridades: a mesma progressao, quatro roupas")
    y = subtitle(d, "Mudam o ritmo, a densidade e as tensoes; a analise harmonica continua a mesma.", y)
    rows = [["Bossa nova", "7M e 9, baixo em sincope", "suave, conversado"],
            ["Jazz", "ii-V-I, SubV, alterados", "denso, resolvido"],
            ["Blues", "dominantes, 7a menor, blue note", "cru, tenso"],
            ["Rock / pop", "triades, power chords, IV e V", "direto, aberto"]]
    _m10_table(d, y + 30, ["Estilo", "Harmonia tipica", "Sensacao"], rows,
               col_x=[MARGIN + 18, MARGIN + 400, MARGIN + 860], row_h=66)
    return img


def _m10_score(notes, caption):
    h = 420
    img, d = canvas(h, BG)
    frame(d, h)
    y = title(d, caption)
    staff(d, MARGIN + 30, y + 40, W - 2 * MARGIN - 60, notes)
    return img


def d_m10_partitura_turnaround():
    return _m10_score([("C", 4, None), ("E", 4, None), ("G", 4, None), ("B", 4, None),
                       ("C", 4, "#"), ("E", 4, None), ("G", 4, None), ("A", 4, None),
                       ("D", 4, None), ("F", 4, None), ("A", 4, None), ("C", 5, None),
                       ("G", 3, None), ("B", 3, None), ("D", 4, None), ("F", 4, None)],
                      "Partitura: turnaround C7M - A7 - Dm7 - G7 (arpejos)")


def d_m10_partitura_reharmonizado():
    return _m10_score([("C", 4, None), ("E", 4, None), ("G", 4, None), ("A", 4, None),
                       ("D", 5, None), ("F", 5, None), ("G", 5, None), ("C", 5, None)],
                      "Partitura: a mesma melodia reharmonizada (chega em C)")


def d_m10_partitura_vozes():
    return _m10_score([("E", 4, None), ("E", 4, None), ("F", 4, None), ("F", 4, None),
                       ("G", 4, None), ("A", 4, None), ("B", 4, None), ("D", 5, None)],
                      "Partitura: vozes internas conduzindo por graus proximos")


def d_m10_partitura_verticalizacao():
    return _m10_score([("A", 4, None), ("G", 4, None), ("F", 4, None), ("E", 4, None)],
                      "Partitura: melodia A-G-F-E verticalizada (Am7-G7-F7M-Em7)")


def d_m10_partitura_modal():
    return _m10_score([("D", 4, None), ("F", 4, None), ("A", 4, None), ("B", 4, None),
                       ("C", 5, None), ("A", 4, None), ("F", 4, None), ("D", 4, None)],
                      "Partitura: frase dorica sobre Dm7 (destaca a sexta maior, B)")


DIAGRAMS.update({
    "m10_analise_harmonica": d_m10_analise_harmonica,
    "m10_analise_melodica": d_m10_analise_melodica,
    "m10_escolha_modal": d_m10_escolha_modal,
    "m10_verticalizacao": d_m10_verticalizacao,
    "m10_conexao_campos": d_m10_conexao_campos,
    "m10_vozes_internas": d_m10_vozes_internas,
    "m10_reharmonizacao": d_m10_reharmonizacao,
    "m10_harmonia_alvo": d_m10_harmonia_alvo,
    "m10_ferramentas": d_m10_ferramentas,
    "m10_estilos": d_m10_estilos,
    "m10_partitura_turnaround": d_m10_partitura_turnaround,
    "m10_partitura_reharmonizado": d_m10_partitura_reharmonizado,
    "m10_partitura_vozes": d_m10_partitura_vozes,
    "m10_partitura_verticalizacao": d_m10_partitura_verticalizacao,
    "m10_partitura_modal": d_m10_partitura_modal,
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
    header = os.path.join(os.path.dirname(out_dir), "ScoreNotes.h")
    _write_score_notes_header(header)
    print(f"{len(SCORE_NOTES)} partituras -> {header}")
    print(f"{len(DIAGRAMS)} diagramas, {total // 1024} KB no total -> {out_dir}")


if __name__ == "__main__":
    main()
