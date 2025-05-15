<?php
// Database connection
$servername = "localhost"; // Change to your database server
$username = "root"; // Change to your database username
$password = ""; // If no password
$dbname = "DB2"; // Your database name


$conn = new mysqli($servername, $username, $password, $dbname);


$eligible_sections = [];


if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $course_id = $_POST['course_id'];
    $student_id = $_POST['student_id'];
    $year = (string) $_POST['year']; 
    $semester = (string) $_POST['semester'];
    
    // Query to get eligible sections
    $current_sections = $conn->query("SELECT section_id FROM section WHERE course_id = '$course_id'
        AND semester = '$semester' AND year = '$year'");

    
    // Fetch eligible sections into the array
    while($row = $current_sections->fetch_assoc()) {
        $eligible_sections[] = $row['section_id'];
    }

}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Course Registration</title>
</head>
<body>
    <h1>Course Registration</h1>
    
    <table border="1">
        <tr>
            <th>Course ID</th>
            <th>Semester</th>
            <th>Year</th>
            <th>Eligible Sections</th>
        </tr>
        <tr>
            <!-- Displays course_id semester, and year in a tables-->
            <td><?php echo htmlspecialchars($course_id); ?></td>
            <td><?php echo htmlspecialchars($semester); ?></td>
            <td><?php echo htmlspecialchars($year); ?></td>
            <td>
                <?php
                // Display eligible sections in the table, which matches the course id semester and year
                if (count($eligible_sections) > 0) {
                    echo '<ul>';
                    foreach ($eligible_sections as $section) {
                        echo '<li>' . $section . '</li>';
                    }
                    echo '</ul>';
                } else {
                    echo 'No eligible sections found for this course.';
                }
                ?>
            </td>
        </tr>
    </table>

    <br><br>
    <!-- Sends the course id, semester and year to the backend as a hidden value because we need them -->
    <form action="register_course.php" method="post">
        <input type="hidden" name="course_id" value="<?php echo htmlspecialchars($course_id); ?>">
        <input type="hidden" name="student_id" value="<?php echo htmlspecialchars($student_id); ?>">
        <input type="hidden" name="semester" value="<?php echo htmlspecialchars($semester); ?>">
        <input type="hidden" name="year" value="<?php echo htmlspecialchars($year); ?>">

        <?php 
        // Display eligible sections in a dropdown
        if (count($eligible_sections) > 0) {
            echo '<label for="section_id">Select Section:</label>'; 
            echo '<select name="section_id" id="section_id" required>';
            foreach ($eligible_sections as $section) {
                echo '<option value="' . $section . '"> ' . $section . '</option>';
            }
            echo '</select>';
        } else {
            echo 'No eligible sections found for this course.';
            exit;
        }
        ?>

        <br><br>
        <button type="submit">Enroll!</button>
    </form>

</body>
</html>