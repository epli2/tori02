# tori02
画像映像コンテンツ演習4

## 環境
- openFrameworks 0.9.8
  - ofxLeapMotion2 ([https://github.com/genekogan/ofxLeapMotion2](https://github.com/genekogan/ofxLeapMotion2))
- Microsoft Visual Studio 2015
- Leap Motion SDK v2.3.1

## How to Use
- openframeworksをダウンロード([download](http://openframeworks.cc/download/))
- 解凍してできたフォルダの中にあるapps/myApps以下にこのリポジトリを`git clone`
- `of_v0.9.8_vs_release/apps/myApps/tori02`となるようにする
- ofxLeapMotion2をインストール([https://github.com/genekogan/ofxLeapMotion2#installation](https://github.com/genekogan/ofxLeapMotion2#installation))
- Visual Studioを起動し、`tori02.vcxproj`を開く
- tori02の構成プロパティから`リンカー/全般/追加のライブラリディレクトリ`に`..¥..¥..¥addons¥ofxLeapMotion2¥libs¥lib¥winvs`を追加
- 続けて`リンカー/入力/追加の依存ファイル`に`Leap.lib`と`Leapd.lib`を追加
- ビルドすると`tori02/bin`以下に実行ファイルができる
- 同ディレクトリに`Leap.dll`を配置する
- ディレクトリ`tori02/bin/data`を作り`tori02/bin/data/models`以下にモデルファイル、`tori02/bin/data/shader`以下にシェーダファイルを配置する

## For Dimenco
- `ofApp.h`の`#define USE_DIMENCO_OPENGL_INTERFACE`のコメントアウトを外す
- `tori02/bin`以下に大学から配布された`opengl32.dll`を配置する
