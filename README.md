# gitHeatmapSVG

1. createHeatmap.bashの`$scriptPath`の値をcreateHeatmap.bashのあるディレクトリへのフルパスに書き変える。
2. パスの通っている(環境変数$PATHに含まれている)ディレクトリにcreateHeatmap.bashへのシンボリックリンクを置く。(シンボリックリンクの名前がコマンド名になる)
3. createHeatmap.bashの実行権限があることを確認する。無い場合は付与する。(chmodコマンド)