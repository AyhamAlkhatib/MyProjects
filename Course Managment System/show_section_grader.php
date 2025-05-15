<?php 
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);

$eligible_students = [];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $course_id = (string) $_POST['course_id'];
    if (isset($_POST['student_info'])) {
        $student_info = $_POST['student_info'];
        
        list($student_id, $standing) = explode('|', $student_info);
        
        $student_id = (string)$student_id; 
        $standing = (string)$standing;      
    } 
    $semester = $_POST['semester'];
    $year = $_POST['year'];

    // Checking if the grader is already a grader by checking for the number of rows that is returned that matches the student_id
    // For the given semester and year
    $check_grader_master = $conn->query("SELECT * FROM masterGrader WHERE semester = '$semester' AND 
        year = '$year' AND course_id = '$course_id'");
    $check_grader_ug = $conn->query("SELECT * FROM undergraduateGrader WHERE semester = '$semester' AND 
        year = '$year' AND course_id = '$course_id'");

    // If there is more than one row then student is a grader
    if ($check_grader_master->num_rows > 0 || $check_grader_ug->num_rows > 0) {
        echo "<table border='1' cellpadding='5' cellspacing='0'>
                <tr><td colspan='2'><strong>A Student is already a grader for this Section.</strong></td></tr>
              </table>";
        exit;
    }

    $eligible_sections = [];

    // Returning the section and grade for that year and semester
    $current_sections = $conn->query("SELECT section_id, grade FROM take WHERE course_id = '$course_id' AND semester = '$semester'
        AND year = '$year'");

    while($row = $current_sections->fetch_assoc()) {
        $section = $row['section_id'];
        $grade = $row['grade'];

        // Query returns the table where section_id semester and year matches to check the number of students enrolled in that
        // section
        $check_num_students = $conn->query("SELECT * FROM take WHERE section_id = '$section' AND semester = '$semester'
            AND year = '$year'");

        if (in_array($section, $eligible_sections)) {
            continue; 
        }

        // If grade is empty, which means that section is being taught the current semester, and query returned a table where there
        // are rows between and including 5-10 students, I would put them in an eligible_section array
        if (empty($grade) && $check_num_students->num_rows >= 5 && $check_num_students->num_rows <= 10) {
            $eligible_sections[] = $section;  
        }
    }
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<body>
    <form action="assign_grader.php" method="post">
        <input type="hidden" name="standing" value="<?php echo htmlspecialchars($standing); ?>">
        <table border="1">
            <tr>
                <td colspan="2"><strong>Assign a Grader for Course</strong></td>
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
                <td><strong>Select Section (Only sections that have 5-10 students are shown):</strong></td>
                <td>
                    <?php 
                    if (count($eligible_sections) > 0) { 
                        echo '<select name="section_id" required>';
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
                    <button type="submit">Assign Grader</button>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>