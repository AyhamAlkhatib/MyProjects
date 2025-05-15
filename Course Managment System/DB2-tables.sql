create table account
	(email		varchar(50),
	 password	varchar(20) not null,
	 type		varchar(20),
	 primary key(email)
	);


create table department
	(dept_name	varchar(100), 
	 location	varchar(100), 
	 primary key (dept_name)
	);

create table instructor
	(instructor_id		varchar(10),
	 instructor_name	varchar(50) not null,
	 title 			varchar(30),
	 dept_name		varchar(100), 
	 email			varchar(50) not null,
	 primary key (instructor_id)
	);


create table student
	(student_id		varchar(10), 
	 name			varchar(20) not null, 
	 email			varchar(50) not null,
	 dept_name		varchar(100),
	 standing  		varchar(100),
	 primary key (student_id)
	);

create table PhD
	(student_id			varchar(10), 
	 qualifier			varchar(30), 
	 proposal_defence_date		date,
	 dissertation_defence_date	date, 
	 primary key (student_id),
	 foreign key (student_id) references student (student_id)
		on delete cascade
	);

create table master
	(student_id		varchar(10), 
	 total_credits		int,	
	 primary key (student_id),
	 foreign key (student_id) references student (student_id)
		on delete cascade
	);

create table undergraduate
	(student_id		varchar(10), 
	 total_credits		int,
	 class_standing		varchar(10)
		check (class_standing in ('Freshman', 'Sophomore', 'Junior', 'Senior')), 	
	 primary key (student_id),
	 foreign key (student_id) references student (student_id)
		on delete cascade
	);

create table classroom
	(classroom_id 		varchar(8),
	 building		varchar(15) not null,
	 room_number		varchar(7) not null,
	 capacity		numeric(4,0),
	 primary key (classroom_id)
	);

create table time_slot
	(time_slot_id		varchar(8),
	 day			varchar(10) not null,
	 start_time		time not null,
	 end_time		time not null,
	 primary key (time_slot_id)
	);

create table course
	(course_id		varchar(20), 
	 course_name		varchar(50) not null, 
	 credits		numeric(2,0) check (credits > 0),
	 primary key (course_id)
	);

create table section
	(course_id		varchar(20),
	 section_id		varchar(10), 
	 semester		varchar(6)
			check (semester in ('Fall', 'Winter', 'Spring', 'Summer')), 
	 year			numeric(4,0) check (year > 1990 and year < 2100), 
	 instructor_id		varchar(10),
	 classroom_id   	varchar(8),
	 time_slot_id		varchar(8),	
	 primary key (course_id, section_id, semester, year),
	 foreign key (course_id) references course (course_id)
		on delete cascade,
	 foreign key (instructor_id) references instructor (instructor_id)
		on delete set null,
	 foreign key (time_slot_id) references time_slot(time_slot_id)
		on delete set null,
	 foreign key (classroom_id) references classroom(classroom_id)
		on delete set null
	);

CREATE TABLE teacherTaught (
    course_id     VARCHAR(20),
    section_id    VARCHAR(10), 
    semester      VARCHAR(6) CHECK (semester IN ('Fall', 'Winter', 'Spring', 'Summer')), 
    year          NUMERIC(4,0) CHECK (year > 1990 AND year < 2100), 
    instructor_id VARCHAR(10),
    PRIMARY KEY (instructor_id, course_id, section_id, semester, year),
    FOREIGN KEY (course_id, section_id, semester, year) 
        REFERENCES section (course_id, section_id, semester, year) 
        ON DELETE CASCADE,
    FOREIGN KEY (instructor_id) 
        REFERENCES instructor (instructor_id) 
);

create table prereq
	(course_id		varchar(20), 
	 prereq_id		varchar(20) not null,
	 primary key (course_id, prereq_id),
	 foreign key (course_id) references course (course_id)
		on delete cascade,
	 foreign key (prereq_id) references course (course_id)
	);

create table advise
	(instructor_id		varchar(8),
	 student_id		varchar(10),
	 start_date		date not null,
	 end_date		date,
	 primary key (instructor_id, student_id),
	 foreign key (instructor_id) references instructor (instructor_id)
		on delete  cascade,
	 foreign key (student_id) references PhD (student_id)
		on delete cascade
);

create table TA
	(student_id		varchar(10),
	 course_id		varchar(8),
	 section_id		varchar(10), 
	 semester		varchar(6),
	 year			numeric(4,0),
	 primary key (student_id, course_id, section_id, semester, year),
	 foreign key (student_id) references PhD (student_id)
		on delete cascade,
	 foreign key (course_id, section_id, semester, year) references 
	     section (course_id, section_id, semester, year)
		on delete cascade
);

create table masterGrader
	(student_id		varchar(10),
	 course_id		varchar(8),
	 section_id		varchar(10), 
	 semester		varchar(6),
	 year			numeric(4,0),
	 primary key (student_id, course_id, section_id, semester, year),
	 foreign key (student_id) references master (student_id)
		on delete cascade,
	 foreign key (course_id, section_id, semester, year) references 
	     section (course_id, section_id, semester, year)
		on delete cascade
);

create table undergraduateGrader
	(student_id		varchar(10),
	 course_id		varchar(8),
	 section_id		varchar(10), 
	 semester		varchar(6),
	 year			numeric(4,0),
	 primary key (student_id, course_id, section_id, semester, year),
	 foreign key (student_id) references undergraduate (student_id)
		on delete cascade,
	 foreign key (course_id, section_id, semester, year) references 
	     section (course_id, section_id, semester, year)
		on delete cascade
);

create table take
	(student_id		varchar(10), 
	 course_id		varchar(8),
	 section_id		varchar(10), 
	 semester		varchar(6),
	 year			numeric(4,0),
	 grade		    	varchar(2)
		check (grade in ('A+', 'A', 'A-','B+', 'B', 'B-','C+', 'C', 'C-','D+', 'D', 'D-','F')), 
	 primary key (student_id, course_id, section_id, semester, year),
	 foreign key (course_id, section_id, semester, year) references 
	     section (course_id, section_id, semester, year)
		on delete cascade,
	 foreign key (student_id) references student (student_id)
		on delete cascade
	);

create table waitlist
	(student_id		varchar(10), 
	 course_id		varchar(8),
	 section_id		varchar(10), 
	 semester		varchar(6),
	 year			numeric(4,0),
	 primary key (student_id, course_id, section_id, semester, year),
	 foreign key (course_id, section_id, semester, year) references 
	     section (course_id, section_id, semester, year)
		on delete cascade,
	 foreign key (student_id) references student (student_id)
		on delete cascade,
	timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
	);

CREATE TABLE rating (
    student_id       VARCHAR(10),
	instructor_name  VARCHAR(50),
    course_id        VARCHAR(8),
    section_id       VARCHAR(10), 
    semester         VARCHAR(6),
    year             NUMERIC(4,0),
    quality          INT,
    difficulty       INT,
    take_again       VARCHAR(3),
    for_credit       VARCHAR(3),
    attendance       VARCHAR(3),
    tags             TEXT,
    PRIMARY KEY (student_id, instructor_name, course_id, section_id, semester, year),
    FOREIGN KEY (course_id, section_id, semester, year) 
        REFERENCES section (course_id, section_id, semester, year)
        ON DELETE CASCADE,
    FOREIGN KEY (student_id) 
        REFERENCES student (student_id)
        ON DELETE CASCADE
);


-- Adnin & Instructors:
insert into account (email, password, type) values ('admin@uml.edu', '123456', 'admin');
insert into account (email, password, type) values ('dbadams@cs.uml.edu', '123456', 'instructor');
insert into account (email, password, type) values ('slin@cs.uml.edu', '123456', 'instructor');
insert into account (email, password, type) values ('Yelena_Rykalova@uml.edu', '123456', 'instructor');
insert into account (email, password, type) values ('Johannes_Weis@uml.edu', '123456', 'instructor');
insert into account (email, password, type) values ('Charles_Wilkes@uml.edu', '123456', 'instructor');
-- Students:
insert into account (email, password, type) values ('jim@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('james@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('jack@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('john@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('tom@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('michael@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('david@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('chris@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('daniel@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('matthew@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('andrew@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('joshua@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('ryan@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('kevin@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('brian@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('william@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('timothy@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('steven@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('eric@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('mark@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('jason@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('paul@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('kenneth@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('ronald@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('donald@student.uml.edu', '123456', 'student');
insert into account (email, password, type) values ('anthony@student.uml.edu', '123456', 'student');

insert into course (course_id, course_name, credits) values ('COMP1010', 'Computing I', 3);
insert into course (course_id, course_name, credits) values ('COMP1020', 'Computing II', 3);
insert into course (course_id, course_name, credits) values ('COMP2010', 'Computing III', 3);
insert into course (course_id, course_name, credits) values ('COMP2300', 'Introduction to Computer Security', 3);
insert into course (course_id, course_name, credits) values ('COMP2040', 'Computing IV', 3);
insert into course (course_id, course_name, credits) values ('COMP3010', 'Organization of Programming Languages', 3);

insert into department (dept_name, location) values ('Miner School of Computer & Information Sciences', 'Dandeneau Hall, 1 University Avenue, Lowell, MA 01854');

insert into student (student_id, name, email, dept_name, standing) values ('a', 'jim', 'jim@student.uml.edu', 'Miner School of Computer & Information Sciences', 'PhD');
insert into student (student_id, name, email, dept_name, standing) values ('b', 'james', 'james@student.uml.edu', 'Miner School of Computer & Information Sciences', 'PhD');
insert into student (student_id, name, email, dept_name, standing) values ('c', 'jack', 'jack@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Master');
insert into student (student_id, name, email, dept_name, standing) values ('d', 'john', 'john@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Master');
insert into student (student_id, name, email, dept_name, standing) values ('e', 'tom', 'tom@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('f', 'michael', 'michael@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('g', 'david', 'david@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('h', 'chris', 'chris@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('i', 'daniel', 'daniel@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('j', 'matthew', 'matthew@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('k', 'andrew', 'andrew@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('l', 'joshua', 'joshua@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('m', 'ryan', 'ryan@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('n', 'kevin', 'kevin@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('o', 'brian', 'brian@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('p', 'william', 'william@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('q', 'timothy', 'timothy@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('r', 'steven', 'steven@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('s', 'eric', 'eric@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('t', 'mark', 'mark@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('u', 'jason', 'jason@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('v', 'paul', 'paul@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('w', 'kenneth', 'kenneth@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('x', 'ronald', 'ronald@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('y', 'donald', 'donald@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');
insert into student (student_id, name, email, dept_name, standing) values ('z', 'anthony', 'anthony@student.uml.edu', 'Miner School of Computer & Information Sciences', 'Undergraduate');

insert into instructor (instructor_id, instructor_name, title, dept_name, email) values ('1', 'David Adams', 'Teaching Professor', 'Miner School of Computer & Information Sciences','dbadams@cs.uml.edu');
insert into instructor (instructor_id, instructor_name, title, dept_name, email) values ('2', 'Sirong Lin', 'Associate Teaching Professor', 'Miner School of Computer & Information Sciences','slin@cs.uml.edu');
insert into instructor (instructor_id, instructor_name, title, dept_name, email) values ('3', 'Yelena Rykalova', 'Associate Teaching Professor', 'Miner School of Computer & Information Sciences', 'Yelena_Rykalova@uml.edu');
insert into instructor (instructor_id, instructor_name, title, dept_name, email) values ('4', 'Johannes Weis', 'Assistant Teaching Professor', 'Miner School of Computer & Information Sciences','Johannes_Weis@uml.edu');
insert into instructor (instructor_id, instructor_name, title, dept_name, email) values ('5', 'Tom Wilkes', 'Assistant Teaching Professor', 'Miner School of Computer & Information Sciences','Charles_Wilkes@uml.edu');
INSERT INTO instructor (instructor_id, instructor_name, title, dept_name, email) values ('6', 'Cindy Chen', 'Professor', 'Miner School of Computer & Information Sciences', 'cchen@cs.uml.edu');
INSERT INTO instructor (instructor_id, instructor_name, title, dept_name, email) values ('7', 'Reza Azadeh', 'Associate Professor', 'Miner School of Computer & Information Sciences', 'rjohnson@cs.uml.edu');
INSERT INTO instructor (instructor_id, instructor_name, title, dept_name, email) values ('8', 'Mohamed Alam', 'Assistant Professor', 'Miner School of Computer & Information Sciences', 'edavis@cs.uml.edu');

insert into time_slot (time_slot_id, day, start_time, end_time) values ('TS1', 'MoWeFr', '11:00:00', '11:50:00');
insert into time_slot (time_slot_id, day, start_time, end_time) values ('TS2', 'MoWeFr', '12:00:00', '12:50:00');
insert into time_slot (time_slot_id, day, start_time, end_time) values ('TS3', 'MoWeFr', '13:00:00', '13:50:00');
insert into time_slot (time_slot_id, day, start_time, end_time) values ('TS4', 'TuTh', '11:00:00', '12:15:00');
insert into time_slot (time_slot_id, day, start_time, end_time) values ('TS5', 'TuTh', '12:30:00', '13:45:00');
INSERT INTO time_slot (time_slot_id, day, start_time, end_time) VALUES ('TS6', 'MoWeFr', '13:00:00', '13:50:00');
INSERT INTO time_slot (time_slot_id, day, start_time, end_time) VALUES ('TS7', 'MoWeFr', '14:00:00', '14:50:00');
INSERT INTO time_slot (time_slot_id, day, start_time, end_time) VALUES ('TS8', 'MoWeFr', '15:00:00', '15:50:00');
INSERT INTO time_slot (time_slot_id, day, start_time, end_time) VALUES ('TS9', 'TuTh', '09:30:00', '10:45:00');


insert into classroom (classroom_id, building, room_number, capacity) values (20, 'olsen hall', 50, 15);
insert into classroom (classroom_id, building, room_number, capacity) values (30, 'olsen hall', 60, 15);
insert into classroom (classroom_id, building, room_number, capacity) values (40, 'olsen hall', 70, 15);
insert into classroom (classroom_id, building, room_number, capacity) values (50, 'olsen hall', 80, 15);
insert into classroom (classroom_id, building, room_number, capacity) values (60, 'olsen hall', 90, 15);
insert into classroom (classroom_id, building, room_number, capacity) values (70, 'olsen hall', 100, 15);
insert into classroom (classroom_id, building, room_number, capacity) values (80, 'olsen hall', 110, 15);

insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP1010', 'Section101', 'Fall', 2022, '1', '20', 'TS1');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP1010', 'Section102', 'Fall', 2022, '1', '20', 'TS2');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP1010', 'Section103', 'Fall', 2022, '2', '30', 'TS3');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP1010', 'Section104', 'Fall', 2022, '3', '40', 'TS4');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP1020', 'Section101', 'Spring', 2023, '1', '20', 'TS1');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP1020', 'Section102', 'Spring', 2023, '1', '20', 'TS2');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP2010', 'Section101', 'Fall', 2024, '4', '30', 'TS2');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP2010', 'Section102', 'Fall', 2024, '4', '30', 'TS3');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP2040', 'Section201', 'Winter', 2025, '2', '30', 'TS5');
-- Current Semester:
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP1010', 'Section101', 'Spring', 2025, '1', '20', 'TS1');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP1010', 'Section102', 'Spring', 2025, '7', '30', 'TS1');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP1020', 'Section101', 'Spring', 2025, '2', '80', 'TS8');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP2010', 'Section101', 'Spring', 2025, '1', '20', 'TS2');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP2010', 'Section102', 'Spring', 2025, '2', '30', 'TS2');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP2010', 'Section103', 'Spring', 2025, '3', '40', 'TS3');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP2040', 'Section101', 'Spring', 2025, '3', '40', 'TS4');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP2040', 'Section102', 'Spring', 2025, '4', '50', 'TS4');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP2300', 'Section101', 'Spring', 2025, '4', '50', 'TS5');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP2300', 'Section102', 'Spring', 2025, '5', '60', 'TS5');
insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP3010', 'Section101', 'Spring', 2025, '5', '60', 'TS6');

insert into prereq (course_id, prereq_id) values ('COMP1020', 'COMP1010');
insert into prereq (course_id, prereq_id) values ('COMP2010', 'COMP1020');
insert into prereq (course_id, prereq_id) values ('COMP2300', 'COMP1020');
insert into prereq (course_id, prereq_id) values ('COMP3010', 'COMP2010');
insert into prereq (course_id, prereq_id) values ('COMP2040', 'COMP2010');

insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP1010', 'Section101', 'Fall', 2022, '1');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP1010', 'Section102', 'Fall', 2022, '1');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP1010', 'Section103', 'Fall', 2022, '2');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP1010', 'Section104', 'Fall', 2022, '3');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP1020', 'Section101', 'Spring', 2023, '1');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP1020', 'Section102', 'Spring', 2023, '1');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP2010', 'Section101', 'Fall', 2024, '4');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP2010', 'Section102', 'Fall', 2024, '4');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP2040', 'Section201', 'Winter', 2025, '2');
-- Current Semester
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP1010', 'Section101', 'Spring', 2025, '1');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP1010', 'Section102', 'Spring', 2025, '7');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP1020', 'Section101', 'Spring', 2025, '2');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP2010', 'Section101', 'Spring', 2025, '1');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP2010', 'Section102', 'Spring', 2025, '2');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP2010', 'Section103', 'Spring', 2025, '3');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP2040', 'Section101', 'Spring', 2025, '3');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP2040', 'Section102', 'Spring', 2025, '4');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP2300', 'Section101', 'Spring', 2025, '4');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP2300', 'Section102', 'Spring', 2025, '5');
insert into teacherTaught(course_id, section_id, semester, year, instructor_id) values ('COMP3010', 'Section101', 'Spring', 2025, '5');


insert into master (student_id, total_credits) values ('c', 135);
insert into master (student_id, total_credits) values ('d', 140);

insert into take (student_id, course_id, section_id, semester, year, grade) values ('a', 'COMP1010', 'Section101', 'Fall', 2022, 'A');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('b', 'COMP1010', 'Section102', 'Fall', 2022, 'A-');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('e', 'COMP1010', 'Section102', 'Fall', 2022, 'A-');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('b', 'COMP1020', 'Section101', 'Spring', 2023, 'A-');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('c', 'COMP1010', 'Section101', 'Fall', 2022, 'A');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('d', 'COMP1010', 'Section102', 'Fall', 2022, 'C');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('c', 'COMP1020', 'Section102', 'Spring', 2023, 'A');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('d', 'COMP1020', 'Section102', 'Spring', 2023, 'C');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('e', 'COMP1020', 'Section102', 'Spring', 2023, 'C');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('c', 'COMP2010', 'Section101', 'Fall', 2024, 'A');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('d', 'COMP2010', 'Section102', 'Fall', 2024, 'A');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('e', 'COMP2010', 'Section101', 'Fall', 2024, 'A');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('c', 'COMP2040', 'Section201', 'Winter', 2025, 'A');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('d', 'COMP2040', 'Section201', 'Winter', 2025, 'A');
insert into take (student_id, course_id, section_id, semester, year, grade) values ('e', 'COMP2040', 'Section201', 'Winter', 2025, 'A');
-- Starting from student_id f, insert to a COMP1010 section in spring 2025
-- One section with 15 students, another with 5 
-- insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP1010', 'Section101', 'Spring', 2025, '1', '20', 'TS1');

insert into take (student_id, course_id, section_id, semester, year) values ('f', 'COMP1010', 'Section101', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('g', 'COMP1010', 'Section101', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('h', 'COMP1010', 'Section101', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('i', 'COMP1010', 'Section101', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('j', 'COMP1010', 'Section101', 'Spring', 2025);
-- insert into section (course_id, section_id, semester, year, instructor_id, classroom_id, time_slot_id) values ('COMP1020', 'Section101', 'Spring', 2025, '2', '30', 'TS1');
insert into take (student_id, course_id, section_id, semester, year) values ('k', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('l', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('m', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('n', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('o', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('p', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('q', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('r', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('s', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('t', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('u', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('v', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('w', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('x', 'COMP1010', 'Section102', 'Spring', 2025);
insert into take (student_id, course_id, section_id, semester, year) values ('y', 'COMP1010', 'Section102', 'Spring', 2025);

insert into PhD (student_id, qualifier, proposal_defence_date, dissertation_defence_date) values ('a', 'completed', '2025-05-15', '2025-05-5');
insert into PhD (student_id, qualifier, proposal_defence_date, dissertation_defence_date) values ('b', 'incomplete', '2025-05-15', '2025-05-5');

INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('e', '12', 'Sophomore');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('f', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('g', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('h', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('i', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('j', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('k', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('l', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('m', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('n', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('o', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('p', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('q', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('r', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('s', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('t', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('u', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('v', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('w', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('x', '0', 'Freshman');
INSERT INTO undergraduate (student_id, total_credits, class_standing) values ('y', '0', 'Freshman');
insert into undergraduate (student_id, total_credits, class_standing) values ('z', '0', 'Freshman');
