<!DOCTYPE html>
<html>
<head>
    <title>Assign Grader</title>
</head>
<body>
    <h1>PhD Students:</h1>

    <!-- Form to select a student and find instructors -->
    <form action="fill_information_advise.php" method="post">
        <?php
        $servername = "localhost";
        $username = "root";
        $password = "";
        $dbname = "DB2";

        $conn = new mysqli($servername, $username, $password, $dbname);

        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $instructor_id = (string)$_POST['instructor_id'];

            $result = $conn->query("SELECT student_id FROM advise WHERE instructor_id = '$instructor_id'");

            // Initialize the array to hold eligible students
            $eligible_students = [];

            // Table for displaying student data
            echo '<table border="1">';
            echo '<thead><tr><th>Student Name</th><th>Student ID</th></tr></thead>';
            echo '<tbody>';

            while ($row = $result->fetch_assoc()) {
                $student_id = $row['student_id']; // Correct assignment of student_id
                $student_query = $conn->query("SELECT name FROM student WHERE student_id = '$student_id'");

                if ($student_query->num_rows > 0) {
                    $student_name = $student_query->fetch_assoc()['name'];
                    echo '<tr>';
                    echo '<td>' . $student_name . '</td>';
                    echo '<td>' . $student_id . '</td>';
                    echo '</tr>';

                    $eligible_students[] = ['id' => $student_id, 'name' => $student_name];
                }
            }

            echo '</tbody>';
            echo '</table>';

            if (count($eligible_students) > 0) {
                echo '<label for="student_id">Select a Student: </label>';
                echo '<select name="student_id" id="student_id" required>';
                foreach ($eligible_students as $student) {
                    echo '<option value="' . $student['id'] . '">' . $student['name'] . " (ID: " . $student['id'] . ')</option>';
                }
                echo '</select>';
            } else {
                echo '<p>No eligible students found for this course.</p>';
            }
        }
        ?>

        <br><br>
        <button type="submit">Modify Advise Information!</button>
        <input type="hidden" name="instructor_id" value="<?php echo htmlspecialchars($instructor_id); ?>">
    </form>
</body>
</html>