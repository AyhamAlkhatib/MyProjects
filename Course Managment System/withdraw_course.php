<?php
$servername = "localhost";
$username = "root";
$password = ""; 
$dbname = "DB2"; 

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

$student_id = $_POST['student_id'];
$course_id = $_POST['course_id'];
$section_id = $_POST['section_id'];
$semester = "Spring";
$year = "2025";

$delete_sql = "DELETE FROM take WHERE student_id = '$student_id' AND course_id = '$course_id' AND section_id = '$section_id'";
$conn->query($delete_sql);

$waitlist_sql = "SELECT student_id FROM waitlist WHERE course_id = '$course_id' AND section_id = '$section_id' ORDER BY timestamp ASC LIMIT 1";
$waitlist_result = $conn->query($waitlist_sql);

if ($waitlist_result->num_rows > 0) {
    $row = $waitlist_result->fetch_assoc();
    $waitlisted_student_id = $row['student_id'];

    $enroll_sql = "INSERT INTO take (student_id, course_id, section_id, semester, year) 
                   VALUES ('$waitlisted_student_id', '$course_id', '$section_id', '$semester', '$year')";
    $conn->query($enroll_sql);

    $remove_sql = "DELETE FROM waitlist WHERE student_id = '$waitlisted_student_id' 
                   AND course_id = '$course_id' AND section_id = '$section_id'";
    $conn->query($remove_sql);
}

echo "Course withdrawal successful.";

$conn->close();
?>
<br><br>
<a href="student_main_page.php?student_id=<?php echo $student_id; ?>">
    <button>Student Main Page</button>
</a>