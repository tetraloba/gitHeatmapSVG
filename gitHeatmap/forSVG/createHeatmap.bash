#!/bin/bash

scriptDir="/home/tetraloba/projects/gitHeatmapSVG/gitHeatmap/forSVG"
tmpPath=${scriptDir}"tmp";
# echo $tmpPath; # debug

git log | grep "^Date:" | awk '{print $6, $3, $4}' | uniq -c > $tmpPath;

$scriptDir/createHeatmap $tmpPath "`pwd`/heatmap.svg";
# echo "`pwd`/"; # debug

rm $tmpPath;