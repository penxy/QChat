SELECT 'Table: ' || name AS table_name FROM sqlite_master WHERE type='table';

.separator " | "
.mode column
.headers on


select* from FriendTable;
select* from FriendMessageTable;
select* from MyAddTable;
select* from MyBeAddTable;
select* from UserInfoTable;