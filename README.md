# utf8_to_windows31j_cvt_checker

iconvを用いてutf-8からwindows31jへ変換するとき、例えば結合文字列を含んでいると、

```
iconv: illegal input sequence at position 3
```

みたいに言われます。入力が膨大なとき、先頭からの文字数表記ではわかりにくいですよね？

また最初のエラーに当たると落ちるため、多数の問題を抱えたファイルを検査する場合面倒です。

そこで行ごとに検査を行うツールを制作しました。

## Usage

```
utf8_to_windows31j_cvt_checker <some files>
cat <some file> | utf8_to_windows31j_cvt_checker
```

## Build

### Require

- C++17対応C++コンパイラ
- CMake 3.7 or later
- (libcのiconv実装が使えない環境では)libiconvなど
  - msys2 mingw環境だとコンパイルできても実行できません

### step

```
cmake -B build .
cmake --build build --target utf8_to_windows31j_cvt_checker
```

## test

iutestを利用しています

```
cmake -B build .
cmake --build build --target ci
```
