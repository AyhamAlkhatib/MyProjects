<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $student_id = (string)$_POST['student_id'];
    $instructor_id1 = (string)$_POST['instructor_id1'];
    $instructor_id2 = (string)$_POST['instructor_id2'];
    $start_date1 = $_POST['start_date1'];
    $end_date1 = $_POST['end_date1'];
    $start_date2 = $_POST['start_date2'];
    $end_date2 = $_POST['end_date2'];

    // Check if instructor already an advisee for that student
    if (empty($instructor_id2)) {
        // Check if the first instructor is already assigned to the student
        $check_advise = $conn->query("SELECT * FROM advise WHERE student_id = '$student_id' AND instructor_id = '$instructor_id1'");
        if ($check_advise->num_rows > 0) {
            echo "At least one instructor already an advisee for that student.";
            exit;
        }
    } else {
        // Check if either of the two instructors is already assigned to the student
        $check_advise1 = $conn->query("SELECT * FROM advise WHERE student_id = '$student_id' AND instructor_id = '$instructor_id1'");
        $check_advise2 = $conn->query("SELECT * FROM advise WHERE student_id = '$student_id' AND instructor_id = '$instructor_id2'");
        if ($check_advise1->num_rows > 0 || $check_advise2->num_rows > 0) {
            echo "At least one instructor already an advisee for that student.";
            exit;
        }
    }

    // Ensure the two selected instructors are different
    if ($instructor_id1 === $instructor_id2) {
        echo "Error: You must select two different instructors.";
        exit;
    } elseif (empty($instructor_id2)) {
        // Insert the first instructor and handle NULL for end date if needed
        $advise_query = $conn->query("INSERT INTO advise (instructor_id, student_id, start_date, end_date) 
            VALUES ('$instructor_id1', '$student_id', '$start_date1', " . ($end_date1 ? "'$end_date1'" : "NULL") . ")");
    // if neither instructor_ids are empty    
    } else {
        // Insert the first instructor and handle NULL for end date if needed
        $advise1 = $conn->query("INSERT INTO advise (instructor_id, student_id, start_date, end_date) 
            VALUES ('$instructor_id1', '$student_id', '$start_date1', " . ($end_date1 ? "'$end_date1'" : "NULL") . ")");
        // Insert the second instructor and handle NULL for end date if needed
        $advise2 = $conn->query("INSERT INTO advise (instructor_id, student_id, start_date, end_date) 
            VALUES ('$instructor_id2', '$student_id', '$start_date2', " . ($end_date2 ? "'$end_date2'" : "NULL") . ")");
    }
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Instructor Assignment</title>
</head>
<body>
    <table border="1">
        <!-- If the program reached this line of code then there are no errors and displays some details-->
        <tr>
            <th colspan="2">Assigned Instructor as Advisee Successfully</th>
        </tr>
        <tr>
            <td>Student ID:</td>
            <td><?php echo htmlspecialchars($student_id); ?></td>
        </tr>
        <tr>
            <td>Instructor ID 1:</td>
            <td><?php echo htmlspecialchars($instructor_id1); ?></td>
        </tr>
        <tr>
            <td>Instructor ID 2:</td>
            <td><?php echo htmlspecialchars($instructor_id2); ?></td>
        </tr>
        <tr>
            <td>Start Date for Instructor 1:</td>
            <td><?php echo htmlspecialchars($start_date1); ?></td>
        </tr>
        <tr>
            <td>End Date for Instructor 1:</td>
            <td><?php echo htmlspecialchars($end_date1); ?></td>
        </tr>
        <tr>
            <td>Start Date for Instructor 2:</td>
            <td><?php echo htmlspecialchars($start_date2); ?></td>
        </tr>
        <tr>
            <td>End Date for Instructor 2:</td>
            <td><?php echo htmlspecialchars($end_date2); ?></td>
        </tr>
    </table>

    <br><br>
    <a href="main.html">
        <button>Main Page</button>
    </a>
</body>
</html>