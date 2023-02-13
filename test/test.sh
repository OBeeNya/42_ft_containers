NAME=containers

CONT=("vector" "stack" "map" "set")

for cont in ${CONT[@]}; do

	c++ -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3 "$cont"_test.cpp -DLIB=ft -o $NAME

	./$NAME > "$cont"_ft.txt

	c++ -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3 "$cont"_test.cpp -DLIB=std -o $NAME

	./$NAME > "$cont"_std.txt

	diff "$cont"_ft.txt "$cont"_std.txt > "$cont"_diff.txt

	if [ -s "$cont"_diff.txt ]; then
		echo "differences in" $cont "implementations"
	else
		echo $cont "implementation is ok"
	fi

done

rm ./$NAME
