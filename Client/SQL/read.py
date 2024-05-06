import csv  
import sqlite3  
import sys
import os

file_name = ["../Data/FriendTable.csv", "../Data/FriendMessageTable.csv", "../Data/MyAddTable.csv", "../Data/MyBeAddTable.csv", "../Data/UserInfoTable.csv"]
table_name = ["FriendTable", "FriendMessageTable", "MyAddTable", "MyBeAddTable", "UserInfoTable"]
col_name = [["id", "name"], ["id", "type", "time", "message"], ["id", "name"], ["id", "name"], ["id", "name"]]
def read_to_csv(db_name):
    conn = sqlite3.connect(db_name)  
    cursor = conn.cursor()  
    for i in range(0, len(table_name)): 
        if i == 1:
            cursor.execute(f"SELECT {col_name[i][0]}, {col_name[i][1]}, {col_name[i][2]}, {col_name[i][3]} FROM {table_name[i]}")
        else:
            cursor.execute(f"SELECT {col_name[i][0]}, {col_name[i][1]} FROM {table_name[i]}")  

        with open(file_name[i], 'w', newline='') as csvfile:  
            csvwriter = csv.writer(csvfile)  

            csvwriter.writerow([i[0] for i in cursor.description])   # 写入列名

            rows = cursor.fetchall()
            for row in rows:
                csvwriter.writerow(row)
            csvfile.close()
    conn.commit()
    cursor.close()
    conn.close()

if __name__ == "__main__":  
    db_name = "mydb" + sys.argv[1] + ".db"
    read_to_csv(db_name)
  

   