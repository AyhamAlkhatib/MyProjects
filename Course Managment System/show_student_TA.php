<?php 
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

$eligible_students = [];
$sections = [];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Accepts the course id
    $course_id = $_POST["course_id"];

    echo "<h2>PhD Students to be selected as TA:</h2><br>";
    // Fetches the students who are PhD by matching the student id
    $result = $conn->query("SELECT student_id FROM PhD");

    echo "<table border='1' cellpadding='5' cellspacing='0'>
            <tr><th>Student Name</th><th>Student ID</th></tr>";

    while ($row = $result->fetch_assoc()) {
        $student_id = $row['student_id'];
        // Fetching the name by matching the student id in the student table
        $student_query = $conn->query("SELECT name FROM student WHERE student_id = '$student_id'");
        if ($student_query->num_rows > 0) {
            $student_name = $student_query->fetch_assoc()['name'];
        }   
        // Displaying the student id along their student name in a table and putting them in an array 

        echo "<tr>
                <td>" . $student_name . "</td>
                <td>" . $student_id . "</td>
              </tr>";

        $eligible_students[] = ['id' => $student_id, 'name' => $student_name];
    }

    echo "</table><br><br>";
}

$conn->close();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Assign TA</title>
</head>
<body>

<h1>Assign TA for Course</h1>

<form action="show_section_TA.php" method="post">
    <label for="student_id">Select Student:</label><br><br>
    <!-- Sending the course_id as a hidden value to the backend so I know which course student to register -->
    <input type="hidden" name="course_id" value="<?php echo htmlspecialchars($course_id); ?>">

    <?php 
    // Displaying the student_id and name as an option to be selected from
    if (count($eligible_students) > 0) { 
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
    <!-- Selecting the semester and year as an option -->
    <label for="semester">Select Semester:</label><br><br>
    <select name="semester" id="semester" required>
        <option value="Spring">Spring</option>
        <option value="Summer">Summer</option>
        <option value="Fall">Fall</option>
        <option value="Winter">Winter</option>
    </select>
    <br><br>

    <label for="year">Select Year:</label><br><br>
    <select name="year" id="year" required>
        <?php 
        for ($year = 1990; $year <= 2100; $year++) {
            echo "<option value=\"$year\">$year</option>";
        }
        ?>
    </select>
    <br><br>

    <button type="submit">Show Sections!</button>
</form>

</body>
</html>
