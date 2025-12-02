#pragma once

// エネミーベースの制作完了
// 次に3種類のエネミーを作りたい
#include "Character.h"
#include "Camera.h"

class Enemy:public Character
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Enemy();
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Init()override;
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update()override;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw(const Camera& camera);

	/// <summary>
	/// 各エネミーの位置
	/// </summary>
	/// <returns></returns>
	const Vec2& GetPos() const { return m_pos; }
	void SetPos(const Vec2& p) { m_pos = p; }

	/// <summary>
	/// 各エネミーが生きているか
	/// </summary>
	/// <returns></returns>
	bool IsAlive()const { return m_isAlive; }

	/// <summary>
	/// 各エネミーがキルされたか
	/// </summary>
	void Kill() { m_isAlive = false; }
protected:
	bool m_isAlive;
};

