#include <cstdint>

#include <nds.h>

#include "flappy/game.hpp"

#include "background.h"
#include "player.h"
#include "wall.h"

int main() {
  videoSetMode(MODE_5_2D);
  vramSetBankA(VRAM_A_MAIN_BG);

  consoleDemoInit();

  int bg_id = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
  bgSetPriority(bg_id, 2); // Wallの下に
  dmaCopy(backgroundBitmap, bgGetGfxPtr(bg_id), backgroundBitmapLen);
  dmaCopy(backgroundPal, BG_PALETTE, backgroundPalLen);

  oamInit(&oamMain, SpriteMapping_1D_32, true);

  // スプライト読み込み
  uint16_t *player_gfx =
      oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
  dmaCopy(&playerTiles, player_gfx, playerTilesLen);
  uint16_t *wall_gfx1 =
      oamAllocateGfx(&oamMain, SpriteSize_32x64, SpriteColorFormat_256Color);
  dmaCopy(&wallTiles, wall_gfx1, wallTilesLen);
  uint16_t *wall_gfx2 =
      oamAllocateGfx(&oamMain, SpriteSize_32x64, SpriteColorFormat_256Color);
  dmaCopy(&wallTiles[512], wall_gfx2, wallTilesLen);

  // パレットをVRAMにコピー
  vramSetBankF(VRAM_F_LCD);
  dmaCopy(&playerPal, VRAM_F_EXT_SPR_PALETTE[0], playerPalLen);
  dmaCopy(&wallPal, VRAM_F_EXT_SPR_PALETTE[1], wallPalLen);
  vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);

  // 以下自作ゲームエンジン
  Game game(player_gfx, wall_gfx1, wall_gfx2);

  while (true) {
    scanKeys();
    consoleClear();
    game.update();
    swiWaitForVBlank();
    oamUpdate(&oamMain);
  }

  return 0;
}
