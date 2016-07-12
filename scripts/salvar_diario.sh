#!/bin/bash
SRC_PATH="/home/fer/workspace/C_C++/"
SRC_DIR="estudio/"
SRC_DATA=$SRC_PATH$SRC_DIR
DEST_FILENAME="$(date -I).estudio.tar.gz"
DEST_PATH="/media/sf_C_C++/2016/estudio"
SRC_FINAL_FILE=$SRC_PATH$DEST_FILENAME
LOCAL_SAVE_DIR=$SRC_PATH"save_old_estudio/"

# echo SRC_DATA=$SRC_DATA
# echo DEST_FILENAME=$DEST_FILENAME
# echo DEST_PATH=$DEST_PATH
# echo SRC_FINAL_FILE=$SRC_FINAL_FILE
# echo $LOCAL_SAVE_DIR


#limpiar
for file in $(find . -type f -name "*~" -o -name "*.o" -o -name "*.out"); do rm -f $file;done


if [ ! -d $SRC_DATA ]; then
    echo -e "\n Directory $SRC_DATA not found \n"
    exit 1
fi

if [ ! -d $DEST_PATH ]; then
    echo -e "\n $DEST_PATH not found \n"
    exit 2
fi


tar -czvf  $DEST_FILENAME $SRC_DIR
if [ ! -f $DEST_FILENAME ]; then
    echo -e "\n $DEST_FILENAME not found \n"
    exit 3
fi


cd $DEST_PATH
# echo $PWD

if [ ! -f $SRC_FINAL_FILE ]; then
    echo -e "\n File to save ($SRC_FINAL_FILE) not found \n"
    exit 4
fi
cp $SRC_FINAL_FILE .

if [ ! -f $DEST_FILENAME ]; then
    echo -e "\n $DEST_FILENAME not copied \n"
    exit 5
fi

cd $SRC_PATH
if [ ! -f $SRC_FINAL_FILE ]; then
    echo -e "\n Not in src dir to local saving. \n"
    exit 6
fi
if [ ! -d $LOCAL_SAVE_DIR ]; then
    mkdir $LOCAL_SAVE_DIR
    echo -e "\n $LOCAL_SAVE_DIR created \n"
fi
mv $SRC_FINAL_FILE $LOCAL_SAVE_DIR



echo ""
echo "\n Saving success \n"
echo ""
echo ">> ls -lhrt $DEST_PATH"
ls -lhrt  $DEST_PATH
echo ""
date
echo ""
