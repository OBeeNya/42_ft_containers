CONT=("vector" "stack" "map" "set")

for cont in ${CONT[@]}; do
	rm logs/"$cont"_ft.txt
	rm logs/"$cont"_std.txt
	rm logs/"$cont"_diff.txt
done
