NAME=containers

c++ -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3 main.cpp -DLIB=ft -o $NAME

./$NAME > ft.txt

c++ -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3 main.cpp -DLIB=std -o $NAME

./$NAME > std.txt

diff ft.txt std.txt > diff.txt
