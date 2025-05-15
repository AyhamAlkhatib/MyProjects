<?php 
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

$eligible_students = [];
$sections = [];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $course_id = $_POST["course_id"];
    echo "<h2>Students who took the course with grade A/A- and now a master/undergraduate student:</h2><br>";
    $ug = FALSE;
    $master = FALSE;

    // Query returns the student ids that took that course and their grade is A/A-
    $check_grade = $conn->query("SELECT student_id FROM take WHERE course_id = '$course_id' 
        AND (grade = 'A' OR grade = 'A-')");

    while ($row = $check_grade->fetch_assoc()) {
        // Assigning the student_id to a variable
        $table_student_id = $row['student_id'];
        // Check if the student is an ug
        $student_standing = $conn->query("SELECT student_id FROM undergraduate WHERE student_id = '$table_student_id'");

        // if there is more than one row then there is a student with that student_id as ug and assign true to 
        // preassigned ug variable
        if ($student_standing->num_rows > 0) {  
            $ug = TRUE;
        }
        // if ug remains false then i'd check if the student id matches one of the student_ids in the master table
        if ($ug === FALSE) {  
            $student_standing = $conn->query("SELECT student_id FROM master WHERE student_id = '$table_student_id'");
            // if there is more than one row then student is a master
            if ($student_standing->num_rows > 0) {  
                $master = TRUE;  
            }
        } 
        // If either vars are TRUE then i'd get their name from the student table 
        if ($ug === TRUE || $master === TRUE) {
            $student_name = $conn->query("SELECT name FROM student WHERE student_id = '$table_student_id'");
            $student_name = $student_name->fetch_assoc();
            $student_name = $student_name['name'];

            // Determine the student standing
            if ($ug) {
                $standing = 'Undergraduate';
            } elseif ($master) {
                $standing = 'Master';
            }

            
            // TODO: store eligible students with their standing in an array
            $eligible_students[] = ['id' => $table_student_id, 'name' => $student_name, 'standing' => $standing];
        }
        // reassign ug and master to false for next student evaluation
        $ug = FALSE;
        $master = FALSE;

    }
}

$conn->close();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <title>Select Student and Semester</title>
</head>
<body>
    <form action="show_section_grader.php" method="post">
    <input type="hidden" name="course_id" value="<?php echo htmlspecialchars($course_id); ?>">
        <table border="1" cellpadding="10" cellspacing="0">
            <tr>
                <td><label for="student_id"><strong>Select Student:</strong></label></td>
                <td>
                    <?php 
                    // Display eligible students with their standing and option to select for which year & course
                    if (count($eligible_students) > 0) { 
                        echo '<select name="student_info" id="student_id" required>';
                        foreach ($eligible_students as $student) {
                            // Concatenate the student_id and standing as value
                            echo '<option value="' . $student['id'] . '|' . $student['standing'] . '">' . $student['name'] . " (ID: " . $student['id'] . ") - " . $student['standing'] . '</option>';
                        }
                        echo '</select>';
                    } else {
                        echo 'No eligible students found for this course.';
                        exit;
                    }
                    ?>
                </td>
            </tr>

            <tr>
                <td><label for="semester"><strong>Select Semester:</strong></label></td>
                <td>
                    <select name="semester" id="semester" required>
                        <option value="Spring">Spring</option>
                        <option value="Summer">Summer</option>
                        <option value="Fall">Fall</option>
                        <option value="Winter">Winter</option>
                    </select>
                </td>
            </tr>

            <tr>
                <td><label for="year"><strong>Select Year:</strong></label></td>
                <td>
                    <select name="year" id="year" required>
                        <?php 
                        for ($year = 1990; $year <= 2100; $year++) {
                            echo "<option value=\"$year\">$year</option>";
                        }
                        ?>
                    </select>
                </td>
            </tr>

            <tr>
                <td colspan="2">
                    <button type="submit"><strong>Show Sections!</strong></button>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>