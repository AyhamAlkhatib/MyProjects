<!DOCTYPE html>
<html>
<head>
    <title>Assign Grader</title>
</head>
<body>
    <h1>Advise:</h1>
    <!-- TODO: get the student_id, course_id, section_id, semester, and year -->
    <form action="course_history_GPA_advise.php" method="post">
        <?php
        $servername = "localhost";
        $username = "root";
        $password = "";
        $dbname = "DB2";

        $conn = new mysqli($servername, $username, $password, $dbname);

        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $instructor_id = (string)$_POST['instructor_id'];
            $result = $conn->query("SELECT * FROM advise WHERE instructor_id = '$instructor_id'");
            $eligible_students = []; // Initialize the array

            while ($row = $result->fetch_assoc()) {
                $student_id = $row['student_id'];
                $student_query = $conn->query("SELECT name FROM student WHERE student_id = '$student_id'");
                
                if ($student_query->num_rows > 0) {
                    $student_name = $student_query->fetch_assoc()['name'];
                }

                echo "Student Name: " . $student_name . "<br>" . "Student ID: " . $student_id . "<br><br>";
                
                $eligible_students[] = ['id' => $student_id, 'name' => $student_name];
            }

            if (count($eligible_students) > 0) { 
                echo '<select name="student_id" id="student_id" required>';
                foreach ($eligible_students as $student) {
                    echo '<option value="' . $student['id'] . '">' . $student['name'] . " (ID: " . $student['id'] . ')</option>';
                }
                echo '</select>';
            } else {
                echo 'No students found having you as their advisor.<br><br>';
                header("Location: instructor_main_page.php?instructor_id=$instructor_id");
                exit; 
            }
        }
        ?>
        <br><br>
        <input type="hidden" name="instructor_id" value="<?php echo htmlspecialchars($instructor_id); ?>">

        <!-- TODO: Show the View Course History button only if there are eligible students -->
        <?php if (count($eligible_students) > 0): ?>
            <button type="submit">View Course History!</button>
        <?php endif; ?>
    </form>
</body>
</html>