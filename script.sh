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
sudo mysql -uroot -e "CREATE USER '$MYSQL_USER'@'localhost' IDENTIFIED BY '$MYSQL_USER_PASS'"
sudo mysql -uroot -e "GRANT ALL PRIVILEGES ON *.* TO '$MYSQL_USER'@'localhost'"

# Создание базы данных и таблицы
mysql -u$MYSQL_USER -p$MYSQL_USER_PASS -e "CREATE DATABASE $MYSQL_DATABASE"
mysql -u$MYSQL_USER -p$MYSQL_USER_PASS -e "USE $MYSQL_DATABASE; CREATE TABLE $MYSQL_TABLE (string VARCHAR(255), hash VARCHAR(255))"
