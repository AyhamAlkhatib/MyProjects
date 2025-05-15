<?php
$servername = "localhost";
$username = "root";
$password = ""; 
$dbname = "DB2"; 

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check if the required parameters are present in the URL
if (isset($_GET['student_id']) && isset($_GET['course_id']) && isset($_GET['section_id']) && isset($_GET['semester']) && isset($_GET['year'])) {
    // Retrieve the parameters from the URL
    $student_id = $_GET['student_id'];
    $course_id = $_GET['course_id'];
    $section_id = $_GET['section_id'];
    $semester = $_GET['semester'];
    $year = $_GET['year'];

    // TODO: Insert into the waitlist with criteria above and echo a message
    $sql = $conn->query("INSERT INTO waitlist (student_id, course_id, section_id, semester, year) 
                        VALUES ('$student_id', '$course_id', '$section_id', '$semester', '$year')");

    if ($sql) {
        echo "Section is full. Added to waitlist.";
    } else {
        echo "Error: " . $conn->error;
    }
} else {
    echo "Missing required parameters!";
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
</head>
<body>
    <br><br>
    <!-- Sending student_id to student_main_page.php via URL -->
    <a href="student_main_page.php?student_id=<?php echo $student_id; ?>"><button>Student Main Page</button></a>
</body>
</html>