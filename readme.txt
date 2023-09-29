●タイトル：モンスターシューティング
●ジャンル：シューティングゲーム
●開発環境
・ハードウェア : Windows(i7、メモリ 32GB)
・開発用ＯＳ : Windows10
・統合開発環境： Microsoft Visual Studio 2022
・開発言語 ：C, C++, HLSL
・ライブラリ : directX11,FBXSDK
●操作方法
入力デバイス：キーボード、コントローラー
移動：WASD、左スティック
砲台回転：矢印キー、右スティック
発射：SPACE、Bボタン

●ゲーム説明
弾を発射して、HPが０になるまでモンスターを倒してスコアを稼ぐゲーム

●こだわり
・Mob/Mob.cpp
→Mobを継承してEnemyクラスやTankクラスなどを実装した
→Enemyの移動に線形補間を使用してスムーズに動くようにした

・Assets/Shader/Normalmap.hlsl
→シェーダーでノーマルマップを実装した
→uv スクロールによって海の流れを表現した

・Assets/Shader/OutLine.hlsl
→トゥーンレンダリングを実装した

・Gimmik/AssistBullet.cpp
→弾が進む予測線を実装した

・Gimmik/Bullet.cpp
→弾が進む物理演算を実装した

・Player/Cannon.cpp
→モデルのボーンの位置から弾の進むベクトルを求めた

・Engine/PolyLine.cpp
→polyline によってエフェクトを実装した

・Engine/Global.h
→XMVECTOR から XMFLOAT3 の変換、距離の計算などのよく使用する関数を実装した

・Engine/BillBorad.cpp
→ビルボードを使ったエフェクトにこだわった

・Engine/Gauge.cpp
→HPゲージを実装した

・Engine/Image.cpp
→画像クリックやフェード処理などのよく使う機能をクラスに追加した

・Engine/Model.cpp
→ステージに同じステージを何個も用意する為、フライウェイトパターンを使用した

・定数や変数などの命名規則を意識して組んだ
・モデル、UI の統一感にこだわった