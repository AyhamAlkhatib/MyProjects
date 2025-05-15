<?php 
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

$eligible_students = [];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Accepting all the values that being sent from the previous file
    $course_id = (string) $_POST['course_id'];
    if (isset($_POST['student_info'])) {
        $student_info = $_POST['student_info'];
        
        list($student_id, $standing) = explode('|', $student_info);
        
        $student_id = (string)$student_id;    
    } 
    $semester = $_POST['semester'];
    $year = $_POST['year'];

    // TODO: check if TA is already a TA by returning the number of rows from the TA table where student_id = student_id 
    // for that semester and year
    $check_TA = $conn->query("SELECT * FROM TA WHERE student_id = '$student_id' AND semester = '$semester' AND 
        year = '$year'");
    // if there is more than one row, then the student is a TA for some section in that semester and year
    if ($check_TA->num_rows > 0) {
        echo "<table border='1' cellpadding='5' cellspacing='0'>
                <tr><td colspan='2' style='text-align: center;'><strong>Student is already a TA for a course.</strong></td></tr>
              </table>";
        exit;
    }

    $eligible_sections = [];

    // TODO: returning the sections that is being offered for whatever the course_id is for the same semester and year
    $current_sections = $conn->query("SELECT section_id, grade FROM take WHERE course_id = '$course_id' AND semester = '$semester'
        AND year = '$year'");
    
    while($row = $current_sections->fetch_assoc()) {
        $section = $row['section_id'];
        $grade = $row['grade'];
        // Skip the section if it's already added
        if (in_array($section, $eligible_sections)) {
            continue; 
        }
        // Also returned the grade to check if it's empty or not because if it's not then the course has been taught
        $check_num_students = $conn->query("SELECT * FROM take WHERE section_id = '$section'  AND semester = '$semester'
            AND year = '$year'");
        // If the grade is empty then i'd put them in the eligible_sections array as an option to be selected
        if (empty($grade)) {
            $eligible_sections[] = $section;  
        }
    }
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Assign a TA</title>
</head>
<body>
    <form action="assign_TA.php" method="post">
        <table border="1" cellpadding="5" cellspacing="0">
            <tr>
                <td colspan="2"><strong>Assign a TA for Course</strong></td>
            </tr>
            <tr>
                <td>Course ID:</td>
                <td>
                    <input type="hidden" name="course_id" value="<?php echo htmlspecialchars($course_id); ?>">
                    <?php echo htmlspecialchars($course_id); ?>
                </td>
            </tr>
            <tr>
                <td>Student ID:</td>
                <td>
                    <input type="hidden" name="student_id" value="<?php echo htmlspecialchars($student_id); ?>">
                    <?php echo htmlspecialchars($student_id); ?>
                </td>
            </tr>
            <tr>
                <td>Semester:</td>
                <td>
                    <input type="hidden" name="semester" value="<?php echo htmlspecialchars($semester); ?>">
                    <?php echo htmlspecialchars($semester); ?>
                </td>
            </tr>
            <tr>
                <td>Year:</td>
                <td>
                    <input type="hidden" name="year" value="<?php echo htmlspecialchars($year); ?>">
                    <?php echo htmlspecialchars($year); ?>
                </td>
            </tr>
            <tr>
                <td><strong>Select Section:</strong></td>
                <td>
                    <?php
                    // Displaying the sections as an option to be selected from 
                    if (count($eligible_sections) > 0) { 
                        echo '<select name="section_id" id="section_id" required>';
                        foreach ($eligible_sections as $section) {
                            echo '<option value="' . $section . '">' . $section . '</option>';
                        }
                        echo '</select>';
                    } else {
                        echo 'No eligible sections found for this course.';
                        exit;
                    }
                    ?>
                </td>
            </tr>
            <tr>
                <td colspan="2">
                    <button type="submit">Assign TA</button>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>