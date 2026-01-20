#include <DxLib.h>
#include "SceneController.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "SceneMain.h"
#include "Pad.h"
#include "EffekseerForDXLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウモード設定
	ChangeWindowMode(true);
	// ウィンドウのタイトル変更
	SetMainWindowText("HARUYA");
	// 画面のサイズ変更
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBitNum);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	{
		// Effekseerを使用する際に必ず使う。
		SetUseDirect3DVersion(DX_DIRECT3D_11);

		// Effekseerを初期化する。
		if (Effekseer_Init(8000) == -1)
		{
			DxLib_End();
			return -1;
		}
		// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
		SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
		// DXライブラリのデバイスロストした時のコールバックを設定する。
		Effekseer_SetGraphicsDeviceLostCallbackFunctions();
		// Effekseerに2D描画の設定をする。
		Effekseer_Set2DSetting(Game::kScreenWidth, Game::kScreenHeight);
		// Zバッファを有効にする。
		SetUseZBuffer3D(TRUE);
		// Zバッファへの書き込みを有効にする。
		SetWriteZBuffer3D(TRUE);
	}
	

	

	SceneController controller;
	controller.Init();

	/*SceneMain* m_pScene = new SceneMain;
	m_pScene->Init();*/
	
	while (ProcessMessage() != -1)
	{
		LONGLONG start = GetNowHiPerformanceCount();

		// 前のフレーム描画を消す
		ClearDrawScreen();
		//（ゲーム内容）
		
		Pad::Update();

		controller.Update();
		controller.Draw();
		/*m_pScene->Update();
		m_pScene->Draw();*/
		

		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// 内容を画面に反映
		ScreenFlip();

		// ゲーム速度がどのPCでも同じスピードになる
		while (GetNowHiPerformanceCount() - start < 16667)
		{

		}
	}

	//DrawPixel(320, 240, GetColor(255, 255, 255));	// 点を打つ

	//WaitKey();				// キー入力待ち

	Effkseer_End();				// Effekseerを終了する。
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}