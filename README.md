# short url
Http сервис для сокрашения URL   
URL сокращаются путем преобразования порядкового номера ссылки в число Base62
  
* проект написан на C++ стандарта C++ 17 
* сборка проекта осуществляется через cmake
* проект содержит библиотеки Boost и nlohmann_json
* есть возможность запустить с помощью docker
___
## сборка проекта
Для начала необходимо скопировать репозиторий на локальный компьютер, для этого введите в терминале команду   
*https://github.com/sergey00010/shortUrl.git*
![git clone](http://nextcloud.forcks.ru/apps/files_sharing/publicpreview/fyp7i74YpCJ4A9F?file=/shortUrlDocs/clone_git.jpg&fileId=27678&x=1920&y=1080&a=true&etag=3b34eca91387976c1e7337d77d9fd778)  
после создай директорию build в сюбом удобном месте и перейдите в нее  
*mkdir build && cd build*  
после этого сконфигурируйте cmake командой  
*cmake /home/user/project/*  
вместо ***/home/user/project/*** укажите путь к проекту, который вы ранее скопировали
![cmale](http://nextcloud.forcks.ru/apps/files_sharing/publicpreview/fyp7i74YpCJ4A9F?file=/shortUrlDocs/app/cmake_build.jpg&fileId=27567&x=1920&y=1080&a=true&etag=0c53fed0559e0c4f9ab5c664006bde00)  
после этого необходимо скомпилировать проект командой   
*make*  
после этого в текущей папке появляются исполняемый файл, папка с библиотеками и конфигурационные файлы  
![make](http://nextcloud.forcks.ru/apps/files_sharing/publicpreview/fyp7i74YpCJ4A9F?file=/shortUrlDocs/app/make_build.jpg&fileId=27572&x=1920&y=1080&a=true&etag=fadec2c809e0d0506832cff6f3fbd05c) 
файлы, оставшиеся от cmake можно удалить, они больше не нужны  
*rm -rf CMakeCache.txt CMakeFiles/ Makefile cmake_install.cmake*  
![rm](http://nextcloud.forcks.ru/apps/files_sharing/publicpreview/fyp7i74YpCJ4A9F?file=/shortUrlDocs/app/rm_other_files.jpg&fileId=27575&x=1920&y=1080&a=true&etag=a9e052be43f82c486f69f832b4799cc7)  
далее откройте файл server_config.json в любом удобном для вас редакторе и
поменяйте параметры сервера (порт, на котором будет работать сервер, адрес сервера, если он локально работает, 
то введите адрес 127.0.0.1, если в docker контейнере то 0.0.0.0 и поменяйте публичный адрес сервера, если
такого нету то введите 127.0.0.1:порт сервера, это влияет только на отображение сокращенного url в терминале)  
![edit server param](http://nextcloud.forcks.ru/apps/files_sharing/publicpreview/fyp7i74YpCJ4A9F?file=/shortUrlDocs/app/edit_server_param.jpg&fileId=27569&x=1920&y=1080&a=true&etag=eea0c3a789df0c62030d8dba192e37a0) 
чтобы запустить сервер введите команду   
*./shortUrl*  
если shortUrl не является исполняемым файлом, то чтобы его сделать таковым, введите команду  
*sudo chmod u+x shortUrl*  
![start server](http://nextcloud.forcks.ru/apps/files_sharing/publicpreview/fyp7i74YpCJ4A9F?file=/shortUrlDocs/app/power_on.jpg&fileId=27574&x=1920&y=1080&a=true&etag=38f11049a5d8506d9fdbd168231a0c60)
сервер работает через Json Api, поэтому, чтобы получить сокращенный адрес введите команду   
*curl -X POST http://shorturl.forcks.ru/api/createUrl -H "Content-Type: application/json" -d '{"url":"https://ya.ru"}'*  
Вместо ***shorturl.forcks.ru*** введите адрес своего сервера  
***/api/createUrl*** не удалять  
Вместо ***https://ya.ru*** напишите url, который необходимо сократить
![create link](http://nextcloud.forcks.ru/apps/files_sharing/publicpreview/fyp7i74YpCJ4A9F?file=/shortUrlDocs/app/get_post.jpg&fileId=27566&x=1920&y=1080&a=true&etag=8313ce42e4b30cc52fb0c639610f82a9)  
сервер даст ответ в формате json  
получен сокращенный url: ***http://shorturl.fors.ru/1***  
если перейти по сокращенному url, то выполняется переадресация на оригинальный адрес   
![firefox](http://nextcloud.forcks.ru/apps/files_sharing/publicpreview/fyp7i74YpCJ4A9F?file=/shortUrlDocs/app/go_to_site_ya1.jpg&fileId=27783&x=1920&y=1080&a=true&etag=1a5c7d39b1f8ef06efa6f3a284e95245)  
![firefox](http://nextcloud.forcks.ru/apps/files_sharing/publicpreview/fyp7i74YpCJ4A9F?file=/shortUrlDocs/app/go_to_site_ya2.jpg&fileId=27784&x=1920&y=1080&a=true&etag=33be1d952c5074360247d3f3e525d770)  
ссылки хранятся в json файле в ./urls/urls.json   
![urls](http://nextcloud.forcks.ru/apps/files_sharing/publicpreview/fyp7i74YpCJ4A9F?file=/shortUrlDocs/app/urlsList.jpg&fileId=27573&x=1920&y=1080&a=true&etag=1384f2448d73a52f0726d802f70d6cf0)  
___
## запуск проекта в docker
чтобы запустить проект, необходимо написать команду (не забудьте поменять адрес сервера на 0.0.0.0)  
*docker-compose up*   
![server param](http://nextcloud.forcks.ru/apps/files_sharing/publicpreview/fyp7i74YpCJ4A9F?file=/shortUrlDocs/docker/docker-compose_serverfile.jpg&fileId=27576&x=1920&y=1080&a=true&etag=db2baa1ed4eeef845c41a12db61433e9)  
![docker compose up](http://nextcloud.forcks.ru/apps/files_sharing/publicpreview/fyp7i74YpCJ4A9F?file=/shortUrlDocs/docker/docker-composeup.jpg&fileId=27571&x=1920&y=1080&a=true&etag=497aeeb7fec62a0a96870c04d1c0c87c)  
