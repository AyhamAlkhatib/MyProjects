<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Accepting all values sent to the backend
    $standing = (string) $_POST['standing'];
    $course_id = (string) $_POST['course_id'];
    $student_id = (string) $_POST['student_id'];
    $semester = (string) $_POST['semester'];
    $year = (string) $_POST['year'];
    $section_id = (string) $_POST['section_id'];
    // if standing is ug then insert in ug_grader table and masterGrader table otherwise
    if ($standing == 'Undergraduate') {
        // Insert for undergraduate standing
        $query = "INSERT INTO undergraduateGrader (student_id, course_id, section_id, semester, year) 
                  VALUES ('$student_id', '$course_id', '$section_id', '$semester', '$year')";
        if ($conn->query($query) === TRUE) {
            $message = "Undergraduate student record inserted successfully.";
        }
    } elseif ($standing == 'Master') {
        // Insert for master standing
        $query = "INSERT INTO masterGrader (student_id, course_id, section_id, semester, year) 
                  VALUES ('$student_id', '$course_id', '$section_id', '$semester', '$year')";
        if ($conn->query($query) === TRUE) {
            $message = "Master student record inserted successfully.";
        }
    }
}

$conn->close();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Student Grader Assignment</title>
</head>
<body>

<h2>Student Grader Assignment</h2>
<!-- Displaying the details in a tables -->
<table border="1" cellpadding="10" cellspacing="0" width="60%">
    <tr>
        <th>Field</th>
        <th>Value</th>
    </tr>
    <tr>
        <td>Standing</td>
        <td><?php echo htmlspecialchars($standing); ?></td>
    </tr>
    <tr>
        <td>Course ID</td>
        <td><?php echo htmlspecialchars($course_id); ?></td>
    </tr>
    <tr>
        <td>Student ID</td>
        <td><?php echo htmlspecialchars($student_id); ?></td>
    </tr>
    <tr>
        <td>Semester</td>
        <td><?php echo htmlspecialchars($semester); ?></td>
    </tr>
    <tr>
        <td>Year</td>
        <td><?php echo htmlspecialchars($year); ?></td>
    </tr>
    <tr>
        <td>Section ID</td>
        <td><?php echo htmlspecialchars($section_id); ?></td>
    </tr>
    <tr>
        <td colspan="2"><?php if (isset($message)) { echo $message; } ?></td>
    </tr>
</table>

<br>

<div>
    <a href="admin_main_page.php">
        <button type="button">Admin Main Page</button>
    </a>
</div>

</body>
</html>