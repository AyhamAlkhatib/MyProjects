<?php 
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $student_id = $_POST["student_id"];
    $course_id = $_POST["course_id"];
    $semester = $_POST["semester"];
    $year = $_POST["year"];
    $section_id = $_POST["section_id"];

    // TODO: check if the student was already a TA for one of the sections by matching the student_id in the TA table
    // Also, check if the student is a Phd student
    $check_existing_TA = $conn->query("SELECT student_id FROM TA WHERE student_id = '$student_id'");
    $check_PhD_student = $conn->query("SELECT student_id FROM PhD WHERE student_id = '$student_id'");
    // if there is more than one row returned for returning the table from the TA matching the student_ids then this means student 
    // is already a TA and if the table returned for the PhD student matching the student_ids is 0 then the student isn't a PhD
    // student
    if ($check_existing_TA->num_rows > 0 || $check_PhD_student->num_rows == 0) {
        echo "Error, student was a TA or student is not a PhD student.";
        exit;
    } else {
        // TODO: check if the section has already at least 10 students enrolled by counting the number of rows in the take table
        // By matching the course_id, section_id, semester, and year.
        $check_section_enrollment = $conn->query("SELECT student_id FROM take WHERE
            course_id = '$course_id' AND section_id = '$section_id' AND semester = '$semester' AND year = '$year'");
        if ($check_section_enrollment->num_rows > 10) {
            $sql = "INSERT into TA (student_id, course_id, section_id, semester, year) VALUES ('$student_id', 
                '$course_id', '$section_id', '$semester', '$year')";
            if ($conn->query($sql) === TRUE) {
                echo "Successfully Assigned!";
            } else {
                echo "Error while assigning.";
                exit;
            }
        } else {
            echo "Section Doesn't have at least 10 students.";
        }
    }
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
</head>
<body>
    <br><br>
    <a href="admin_main_page.php"><button>Admin Main Page</button></a>
</body>
</html>