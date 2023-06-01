#!/bin/bash

# Переменные для настройки MySQL
MYSQL_USER=Testuser
MYSQL_USER_PASS=13243546Aa@
MYSQL_DATABASE=Base4Test
MYSQL_TABLE=HashTable

# Установка MySQL
sudo apt-get update
sudo apt-get install -y mysql-server libmysqlclient-dev

# Создание пользователя
mysql -uroot -p -e "CREATE USER '$MYSQL_USER'@'localhost' IDENTIFIED BY '$MYSQL_USER_PASS'"
mysql -uroot -p -e "GRANT ALL PRIVILEGES ON *.* TO '$MYSQL_USER'@'localhost'"

# Создание базы данных и таблицы
mysql -uroot -p -e "CREATE DATABASE $MYSQL_DATABASE"
mysql -uroot -p -e "USE $MYSQL_DATABASE; CREATE TABLE $MYSQL_TABLE (string VARCHAR(255), hash VARCHAR(255))"
