import sqlite3
import sys

table_name = ["FriendTable", "FriendMessageTable", "MyAddTable", "MyBeAddTable", "UserInfoTable"]

def Create_Table(database_name):
    conn = sqlite3.connect(database_name)
    cursor = conn.cursor()
    for i in range(0, len(table_name)):
        if i == 1:   #id type time message
            cursor.execute(f'CREATE TABLE IF NOT EXISTS {table_name[i]} (idx AUTO_INCREMENT PRIMARY KEY, id int NOT NULL, type INT NOT NULL, time varchar(30) NOT NULL, message TEXT NOT NULL)')
        else:
            cursor.execute(f'CREATE TABLE IF NOT EXISTS {table_name[i]} (idx AUTO_INCREMENT PRIMARY KEY, id int NOT NULL, name varchar(10) NOT NULL)')

    conn.commit()
    conn.close()

if __name__ == '__main__':
    database_name = 'mydb' + sys.argv[1] + '.db'
    Create_Table(database_name)


