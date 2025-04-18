# Program to generate Markdown from ScrapBox Text
ScrapBoxのテキストをMarkdownに変換するツールです。  
ScrapBoxの装飾を引き継ぎます。  

## コンパイル方法
> g++ -std=c++11 -o scb02md main.cpp

## 使い方
このツールは、ScrapBox形式のテキストファイルを読み込み、Markdown形式に変換したファイルを出力します。

bash
>./scb02md <入力ファイル名> <出力ファイル名>

例)
>./scb02md sample.txt output.md

## 変換仕様
ScrapBoxの記法をMarkdownに対応するように、以下のルールで変換されます：  
| ScrapBox記法             | Markdown変換後      | 備考                                 |
| ------------------------ | ------------------- | ------------------------------------ |
| `[**** メイントピック]`  | `# メイントピック`  | 見出し（レベル1）に変換              |
| `[*** サブタイトル]`     | `## サブタイトル`   | 見出し（レベル2）に変換              |
| `[** タイトル]`          | `### タイトル`      | 見出し（レベル3）に変換              |
| `[* 強調]`               | `**強調**`          | 太字に変換                           |
| 先頭の空白（インデント） | `  ` や `*` を使用  | ネストされたリストに変換             |
| 各行の末尾               | スペース2つ（`  `） | Markdown整形のために自動で付与される |
- 各行の末尾には、Markdownの整形に必要なスペース2つ（ ）が付与されます。

## 注意点
- 入力ファイルの1行目はページタイトルとして処理され、# を先頭に付けたMarkdown見出しとして出力されます。  
- 全角スペース（　）は自動的に半角スペース（ ）に変換されます。  
- 空白やタブに応じて自動的にリスト形式に変換されます。  
- ScrapBox特有の以下の機能には非対応です：
  - 画像表示
  - ハイパーリンク
  - タグ（例： [#Tag] など）