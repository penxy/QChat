import csv  
import sys
import sqlite3


file_name = ["../Data/FriendTable.csv", "../Data/FriendMessageTable.csv", "../Data/MyAddTable.csv", "../Data/MyBeAddTable.csv", "../Data/UserInfoTable.csv"]
table_name = ["FriendTable", "FriendMessageTable", "MyAddTable", "MyBeAddTable", "UserInfoTable"]
col_name = [["id", "name"], ["id", "type", "time", "message"], ["id", "name"], ["id", "name"], ["id", "name"]]

def save_in_sql(db_name):  
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()
    for i in range(0, len(table_name)):
        with open(file_name[i], newline='',encoding='latin1') as csvfile:  
            csvreader = csv.DictReader(csvfile)  
            for row in csvreader:  
                if i == 1:
                    #print(row[col_name[i][0]], row[col_name[i][1]], row[col_name[i][2]], row[col_name[i][3]])
                    insert_query = f'INSERT INTO {table_name[i]} ({col_name[i][0]}, {col_name[i][1]}, {col_name[i][2]}, {col_name[i][3]}) VALUES (?, ?, ?, ?)'
                    cursor.execute(insert_query, (row[col_name[i][0]], row[col_name[i][1]], row[col_name[i][2]], row[col_name[i][3]]))
                else:
                    insert_query = f'INSERT INTO {table_name[i]} ({col_name[i][0]}, {col_name[i][1]}) VALUES (?, ?)'
                    cursor.execute(insert_query, (row[col_name[i][0]], row[col_name[i][1]]))  
    conn.commit()
    cursor.close() 
    conn.close()

if __name__ == '__main__':
    db_name = 'mydb' + sys.argv[1] + '.db'
    save_in_sql(db_name)
