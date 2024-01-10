# 1 - variable name
# 2 - binary file
# 3 - shader variables.c file

size=$(stat --printf="%s" $2)
hex=$(cat $2 | od -An -v -tx1 | tr -d "\n" | sed "s/ /\\\x/g")

if [ ! -f $3 ]; then
    touch $3
fi

echo "const char *$1 = \"$hex\";" >> $3
echo "unsigned ${1}_length = $size;" >> $3
