<?php
$servername = "localhost";
$username = "root";
$password = ""; 
$dbname = "DB2"; 

$conn = new mysqli($servername, $username, $password, $dbname);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $instructor_id = $_POST['instructor_id'];

    // Fetching all courses that the instructor taught
    $instructor_courses = $conn->query("SELECT course_id, section_id, semester, year FROM teacherTaught WHERE instructor_id = '$instructor_id'");

    $previous_courses = "";
    $current_courses = "";

    while ($row = $instructor_courses->fetch_assoc()) {
        $course_id = $row['course_id']; 
        $section_id = $row['section_id'];
        $semester = $row['semester'];
        $year = $row['year'];

        // Fetching the students who took the course with the instructor
        $students = $conn->query("SELECT student_id, grade FROM take WHERE course_id = '$course_id' AND section_id = '$section_id' AND semester = '$semester' AND year = '$year'");

        while ($student = $students->fetch_assoc()) {
            $student_id = $student['student_id'];
            $course_grade = $student['grade'];
            // Then I would get there name from the student table by matching there student ids
            $student_name_query = $conn->query("SELECT name FROM student WHERE student_id = '$student_id'");
            $student_name_row = $student_name_query->fetch_assoc();
            $student_name = $student_name_row['name'];
            // If the course grade is null i would put it in a different table than if the course grade isn't null
            if ($course_grade !== null && $course_grade !== "") {
                $previous_courses .= "<tr><td>$course_id</td><td>$section_id</td><td>$semester</td><td>$year</td><td>$student_name</td><td>$course_grade</td></tr>";
            } else {
                $current_courses .= "<tr><td>$course_id</td><td>$section_id</td><td>$semester</td><td>$year</td><td>$student_name</td><td>Currently Taking</td></tr>";
            }
        }
    }

    echo "<h2>Previous Semester Courses:</h2>";
    echo "<table border='1'>
            <tr>
                <th>Course ID</th>
                <th>Section ID</th>
                <th>Semester</th>
                <th>Year</th>
                <th>Student Name</th>
                <th>Grade</th>
            </tr>";
    echo $previous_courses ?: "<tr><td colspan='6'>No records found.</td></tr>";
    echo "</table><br>";

    
    echo "<h2>Current Semester Courses:</h2>";
    echo "<table border='1'>
            <tr>
                <th>Course ID</th>
                <th>Section ID</th>
                <th>Semester</th>
                <th>Year</th>
                <th>Student Name</th>
                <th>Status</th>
            </tr>";
    echo $current_courses ?: "<tr><td colspan='6'>No records found.</td></tr>";
    echo "</table><br>";
}

$conn->close();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>

    <a href="instructor_main_page.php?instructor_id=<?php echo $instructor_id; ?>"><button>Instructor Main Page</button></a>

</body>
</html>