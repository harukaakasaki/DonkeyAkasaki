#pragma once
namespace Pad
{
	/// <summary>
	/// パッドの更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 押されているか
	/// </summary>
	/// <param name="key">押されているかどうか</param>
	/// <returns></returns>
	bool IsPress(int key);
	/// <summary>
	/// 押された瞬間を取得
	/// </summary>
	/// <param name="key">入力キー</param>
	/// <returns>押されたかどうか</returns>
	bool IsTrigger(int key);
	/// <summary>
	/// 話した瞬間を取得
	/// </summary>
	/// <param name="key">入力キー</param>
	/// <returns>離されたかどうか</returns>
	bool IsRelease(int key);

};

