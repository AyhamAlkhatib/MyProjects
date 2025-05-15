<!DOCTYPE html>
<html>
<head>
    <title>Assign Grader</title>
</head>
<body>
    <h1>PhD Students:</h1>

    <!-- Form to select a student and find instructors -->
    <form action="show_instructors_advise.php" method="post">
        <?php
        $servername = "localhost";
        $username = "root";
        $password = "";
        $dbname = "DB2";

        $conn = new mysqli($servername, $username, $password, $dbname);

        // Returning the student ids from PhD table
        $result = $conn->query("SELECT student_id FROM PhD");

        $eligible_students = [];

        // Table header to print student id and name
        echo '<table border="1">';
        echo '<thead><tr><th>Student Name</th><th>Student ID</th></tr></thead>';
        echo '<tbody>';

        while ($row = $result->fetch_assoc()) {
            // taking the student id and returns the students name matcing the student id in the student table
            $student_id = $row['student_id'];

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
        // Displaying the student name and id as an option to be selected by the admin
        if (count($eligible_students) > 0) {
            echo '<label for="student_id">Select a Student: </label>';
            echo '<select name="student_info" id="student_id" required>';
            foreach ($eligible_students as $student) {
                echo '<option value="' . $student['id'] . '">' . $student['name'] . " (ID: " . $student['id'] . ')</option>';
            }
            echo '</select>';
        } else {
            echo '<p>No eligible students found for this course.</p>';
        }
        ?>

        <br><br>
        <button type="submit">Find Instructors!</button>
    </form>
</body>
</html>
