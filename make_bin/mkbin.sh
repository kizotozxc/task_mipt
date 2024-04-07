#!/bin/bash
start_directory=$(pwd)
while  [ $# -gt 0 ] 
do
  case $1
  in
    -s| --source)
      path=$2
      shift 2
      ;;
    -a| --archive)
      archive=$2
      shift 2
      ;;
    -c| --compiler)
    array_compilers+="$2;"
    shift 2
    ;;
  esac
done

cd "$path" || exit

mkdir "$archive"
# echo $array_compilers 
IFS=';' read -ra str <<< "$array_compilers"
for compiler in "${str[@]}"
do
  IFS='=' read -ra compiling_files <<< "$compiler"
      for (( c=0; c<(${#compiling_files[*]} - 1); c++ ))
      do 
        while IFS=' ' read -r name
        do
          name=$(echo "$name" | cut -c 3-)
          ${compiling_files[(${#compiling_files[*]}-1)]} -o "${name%.*}".exe "$name"
          cp --parents "${name%.*}".exe "$archive"  
          # rsync -R "${name%.*}".exe "$archive"
        done <   <(find . -name "*.${compiling_files[$c]}")
      done
done

tar cf "$start_directory"/"$archive".tar.gz "$archive"
# tar -ztf $archive.tar.gz
rm -rf "$archive"
echo complete
