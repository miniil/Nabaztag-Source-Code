SET FOREIGN_KEY_CHECKS = 0;

delete from `subscriber` where subscriber_user = '16951';
delete from `nabcast` where nabcast_id in (389,374,107,266,172,424,184,259,1135,480,933,959,518,611,290,668,858);
DELETE FROM user WHERE user_id = 195 OR user_id = 84887 OR user_id=777 OR user_id=778;
DELETE FROM annu WHERE annu_user = 84887 OR annu_user = 195 OR annu_user= 777;
DELETE FROM object WHERE object_id = 31;
DELETE FROM object WHERE object_id = 57520;
delete from `object` where object_id = 16951;
delete from `object` where object_id = 16952;
delete from `object_profile` where object_id  IN (57520, 31, 16951, 16952);
delete from `object_preferences` where object_id  = 57520 or object_id  = 31 or object_id  = 16951 or object_id  = 16952;
delete from object where object_serial = 'aaaaaaaaaaaa';
delete from object where object_serial = 'aaaaaaaaaaab';
delete from object where object_serial = 'aaaaaaaaaaac';
delete from files where id =1850108;
update hardware set picture_file_id=NULL where id=4;
delete from files where id =123123;
truncate object_profile;
truncate object_preferences;
SET FOREIGN_KEY_CHECKS = 1;
