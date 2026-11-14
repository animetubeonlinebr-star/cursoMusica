#!/usr/bin/env python3
"""Build the application icon assets from the source artwork.

Source: ico.jpg at the repository root (uploaded on main, commit 602c6c5;
the generated assets are committed so the build needs no Python).

Outputs (committed, so the build needs no Python/Pillow):

  Assets/AppIcon.png  square 512x512 image with the theme background colour
  Assets/AppIcon.ico  16/24/32/48/64/128/256 for Windows (executable + NSIS)

The CMake build passes AppIcon.png to JUCE (ICON_BIG, which generates the .ico
resource for the executable) and embeds it for the window icon; installer.nsi
uses AppIcon.ico for the installer and the shortcuts.
"""

from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parent.parent
SOURCE = ROOT / "ico.jpg"  # the artwork uploaded to main (commit 602c6c5)
PNG_OUT = ROOT / "Assets" / "AppIcon.png"
ICO_OUT = ROOT / "Assets" / "AppIcon.ico"

# Matches theme::colour::background so the square blends with the dark UI.
BACKGROUND = (27, 21, 35)
CANVAS = 512
ICO_SIZES = [(16, 16), (24, 24), (32, 32), (48, 48), (64, 64), (128, 128), (256, 256)]


def content_bounds(image, background, tolerance=24):
    """Bounding box of the pixels that differ from the flat background."""
    width, height = image.size
    pixels = image.load()
    left, top, right, bottom = width, height, -1, -1

    for y in range(height):
        for x in range(width):
            r, g, b = pixels[x, y][:3]
            if (abs(r - background[0]) > tolerance
                    or abs(g - background[1]) > tolerance
                    or abs(b - background[2]) > tolerance):
                left = min(left, x)
                top = min(top, y)
                right = max(right, x)
                bottom = max(bottom, y)

    if right < left or bottom < top:
        return (0, 0, width, height)

    return (left, top, right + 1, bottom + 1)


def main():
    artwork = Image.open(SOURCE).convert("RGB")
    artwork = artwork.crop(content_bounds(artwork, BACKGROUND))

    # Pad the crop to a square so the logo is never distorted.
    side = max(artwork.size)
    square = Image.new("RGB", (side, side), BACKGROUND)
    square.paste(artwork, ((side - artwork.width) // 2, (side - artwork.height) // 2))

    icon = square.resize((CANVAS, CANVAS), Image.LANCZOS)
    icon.save(PNG_OUT)
    icon.save(ICO_OUT, sizes=ICO_SIZES)

    print(f"{PNG_OUT.relative_to(ROOT)}: {icon.size[0]}x{icon.size[1]}")
    print(f"{ICO_OUT.relative_to(ROOT)}: {', '.join(f'{w}x{h}' for w, h in ICO_SIZES)}")


if __name__ == "__main__":
    main()
