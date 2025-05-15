<?php 
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

$eligible_students = [];
$sections = [];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $student_id = (string)$_POST['student_info'];
    
    // Returns the instructor id and name and displays instructor name and id as table header
    $result = $conn->query("SELECT instructor_id, instructor_name FROM instructor");
    
    echo "<h2>Instructors:</h2>";

    echo '<table border="1" cellpadding="5" cellspacing="0">';
    echo '<thead>';
    echo '<tr>';
    echo '<th>Instructor Name</th>';
    echo '<th>Instructor ID</th>';
    echo '</tr>';
    echo '</thead>';
    
    echo '<tbody>';
    // Assigning the instructor_name and id to a variable and displays them in a table
    while ($row = $result->fetch_assoc()) {
        $instructor_name = $row['instructor_name'];
        $instructor_id = $row['instructor_id'];

        echo '<tr>';
        echo '<td>' . $instructor_name . '</td>';
        echo '<td>' . $instructor_id . '</td>';
        echo '</tr>';

        $instructors[] = ['id' => $instructor_id, 'name' => $instructor_name];
    }
    echo '</tbody>';
    echo '</table>';
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
</head>
<body>

    <h2>Don't Select Same Instructors!</h2>
    
    <form action="assign_instructor_advise.php" method="post">
        <input type="hidden" name="student_id" value="<?php echo htmlspecialchars($student_id); ?>">

        <!-- First Instructor Selection -->
        <label for="instructor_id1">Select First Instructor:</label>
        <!-- Displays the instructors name and id -->
        <?php 
        if (count($instructors) > 0) { 
            echo '<select name="instructor_id1" id="instructor_id1">';
            echo '<option value="" disabled selected>Select an instructor</option>';
            foreach ($instructors as $instructor) {
                echo '<option value="' . $instructor['id'] . '">' . $instructor['name'] . " (ID: " . $instructor['id'] . ')</option>';
            }
            echo '</select>';
        } else {
            echo 'No instructors found.';
        }
        ?>
        <br><br>

        <!-- Second Instructor Selection -->
        <label for="instructor_id2">Select Second Instructor:</label>
        <?php 
        if (count($instructors) > 0) { 
            echo '<select name="instructor_id2" id="instructor_id2">';
            echo '<option value="" disabled selected>Select an instructor (Optional)</option>';
            foreach ($instructors as $instructor) {
                echo '<option value="' . $instructor['id'] . '">' . $instructor['name'] . " (ID: " . $instructor['id'] . ')</option>';
            }
            echo '</select>';
        } else {
            echo 'No instructors found.';
        }
        ?>
        <br><br>

        <!-- Start and End Dates for Instructor 1 -->
        <label for="start_date1">Start Date for instructor 1:</label>
        <input type="date" name="start_date1" required><br><br>

        <label for="end_date1">End Date for instructor 1 (Optional):</label>
        <input type="date" name="end_date1"><br><br>

        <!-- Start and End Dates for Instructor 2 -->
        <label for="start_date2">Start Date for instructor 2:</label>
        <input type="date" name="start_date2"><br><br>

        <label for="end_date2">End Date for instructor 2 (Optional):</label>
        <input type="date" name="end_date2"><br><br>

        <!-- Submit Button -->
        <button type="submit">Assign Instructor(s) as Advisee(s)!</button>
    </form>

</body>
</html>
