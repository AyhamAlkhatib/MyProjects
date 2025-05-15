<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['course_info'])) {

    list($course_id, $section_id, $semester, $year, $instructor_name, $grade) = explode('|', $_POST['course_info']);

    $student_id = $_POST['student_id'];
    $quality = $_POST['quality']; 
    $difficulty = $_POST['difficulty']; 
    $take_again = $_POST['take_again']; 
    $for_credit = $_POST['for_credit']; 
    $attendance = $_POST['attendance']; 
    $tags = implode(", ", $_POST['tags']);

    // Insert into rating
    $rate_query = "INSERT INTO rating 
                   (student_id, instructor_name, course_id, section_id, semester, year, quality, difficulty, take_again, for_credit, attendance, tags) 
                   VALUES 
                   ('$student_id', '$instructor_name', '$course_id', '$section_id', '$semester', '$year', '$quality', '$difficulty', '$take_again', '$for_credit', '$attendance', '$tags')";

    if ($conn->query($rate_query) === TRUE) {
        echo "Rating inserted successfully!";
    } else {
        echo "Error: " . $rate_query . "<br>" . $conn->error;
    }
} else {
    echo "No course selected.";
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head></head>
<body>
    <br><br>
    <a href="student_main_page.php?student_id=<?php echo $student_id; ?>"><button>Student Main Page</button></a>
</body>
</html>