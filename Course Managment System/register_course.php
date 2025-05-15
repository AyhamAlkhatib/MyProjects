<?php
// Database connection
$servername = "localhost"; // Change to your database server
$username = "root"; // Change to your database username
$password = ""; // If no password
$dbname = "DB2"; // Your database name

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check if the form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $course_id = $_POST['course_id'];
    $student_id = $_POST['student_id'];
    $year = (string) $_POST['year']; 
    $semester = (string) $_POST['semester'];
    $section_id = $_POST['section_id'];

    // Checking the number of rows because if there is at least one row then student is taking or course been taken
    $check_grade = $conn->query("SELECT * FROM take WHERE course_id = '$course_id' AND student_id = '$student_id'");

    if ($check_grade->num_rows > 0) {
        echo "This course has already been taken or being taken.";
        exit;
    }
    

    // Fetch pre-requisite ID from the pre-req table for that course
    $pre_req_query = "SELECT prereq_id FROM prereq WHERE course_id = '$course_id'";
    $pre_req_result = $conn->query($pre_req_query);
    $pre_req_row = $pre_req_result->fetch_assoc();
    $pre_req_id = $pre_req_row['prereq_id'];

    // Fetch courses the student has already taken
    $student_courses_query = "SELECT course_id FROM take WHERE student_id = '$student_id'";
    $student_courses_result = $conn->query($student_courses_query);
    
    $student_courses = [];
    // putting the student courses in an array
    while ($row = $student_courses_result->fetch_assoc()) {
        $student_courses[] = $row['course_id'];
    }

    if (!in_array($pre_req_id, $student_courses) && $pre_req_id !== NULL) {
        // Student has not completed the pre-requisite course
        echo "Error: You have not completed the required pre-requisite course.";
        $conn->close();
        exit;
    } else {
        // checking if the section has more than 15 students by counting the number of rows in the take table
        $check = "SELECT COUNT(*) as count FROM take WHERE section_id = '$section_id' AND semester = '$semester' 
            AND course_id = '$course_id' AND year = '$year'";
        $result = $conn->query($check);
        $row = $result->fetch_assoc();

        if ($row["count"] >= 15) {
            // Redirect to waitlist if section is full
            header("Location: waitlist.php?student_id=$student_id&course_id=$course_id&section_id=$section_id&semester=$semester&year=$year");
            exit;
        } elseif ($row["count"] < 15) {
            $sql = "INSERT INTO take (student_id, course_id, section_id, semester, year) 
                    VALUES ('$student_id', '$course_id', '$section_id', '$semester', '$year')";
        
            if ($conn->query($sql) === TRUE) {
                echo "Successfully enrolled!";
            } else {
                echo "Error: " . $conn->error;
            }
        }
    }
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Enrollment Status</title>
</head>
<body>
    <h1>Enrollment Details</h1>
    <table border="1">
        <tr>
            <th>Student ID</th>
            <th>Course ID</th>
            <th>Semester</th>
            <th>Year</th>
            <th>Section ID</th>
        </tr>
        <tr>
            <!-- Shows enrollment status as a table by showing the following values -->
            <td><?php echo htmlspecialchars($student_id); ?></td>
            <td><?php echo htmlspecialchars($course_id); ?></td>
            <td><?php echo htmlspecialchars($semester); ?></td>
            <td><?php echo htmlspecialchars($year); ?></td>
            <td><?php echo htmlspecialchars($section_id); ?></td>
        </tr>
    </table>

    <br><br>
    <a href="student_main_page.php?student_id=<?php echo $student_id; ?>"><button>Student Main Page</button></a>
</body>
</html>