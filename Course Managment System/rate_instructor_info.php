<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['student_id'])) {
    $student_id = $_POST['student_id'];

    $course_result = $conn->query("SELECT course_id, grade, section_id, semester, year 
                                   FROM take 
                                   WHERE student_id = '$student_id'");

    if ($course_result->num_rows > 0) {
        echo '<form action="rate_instructor.php" method="post">
              <table border="1">
              <tr>
                  <td><label for="course_info">Course:</label></td>
                  <td>
                      <select name="course_info" required>';
        while ($row = $course_result->fetch_assoc()) {
            $course_id = $row['course_id'];
            $grade = $row['grade'];
            $section_id = $row['section_id'];
            $semester = $row['semester'];
            $year = $row['year'];

            if (!empty($grade)) {
                $instructor_name = "Unknown";

                $instructor_query = "SELECT instructor_id FROM teacherTaught 
                                     WHERE course_id = '$course_id' 
                                     AND section_id = '$section_id' 
                                     AND semester = '$semester' 
                                     AND year = '$year'";
                $instructor_result = $conn->query($instructor_query);
                if ($instructor_result->num_rows > 0) {
                    $instructor_id = $instructor_result->fetch_assoc()['instructor_id'];

                    $instructor_name_result = $conn->query("SELECT instructor_name FROM instructor WHERE instructor_id = '$instructor_id'");
                    if ($instructor_name_result->num_rows > 0) {
                        $instructor_name = $instructor_name_result->fetch_assoc()['instructor_name'];
                    }
                }

                // Include instructor_name in option value
                $option_value = $course_id . '|' . $section_id . '|' . $semester . '|' . $year . '|' . $instructor_name . '|' . $grade;

                echo '<option value="' . htmlspecialchars($option_value) . '">' .
                        $course_id . ' | Section ' . $section_id . ' | ' . $semester . ' ' . $year . ' | ' . $instructor_name .
                     '</option>';
            }
        }
        echo '</select>
              </td>
              </tr>';

        // Rating fields
        echo '
            <tr><td>Professor Rating:</td><td><input type="number" name="quality" min="1" max="5" required></td></tr>
            <tr><td>Difficulty:</td><td><input type="number" name="difficulty" min="1" max="5" required></td></tr>
            <tr><td>Take Again?</td>
                <td><select name="take_again" required><option value="Yes">Yes</option><option value="No">No</option></select></td></tr>
            <tr><td>For Credit?</td>
                <td><select name="for_credit" required><option value="Yes">Yes</option><option value="No">No</option></select></td></tr>
            <tr><td>Attendance Mandatory?</td>
                <td><select name="attendance" required><option value="Yes">Yes</option><option value="No">No</option></select></td></tr>
            <tr><td>Tags:</td>
                <td><select name="tags[]" multiple required>
                        <option value="Lots of homework">Lots of homework</option>
                        <option value="Extra credit available">Extra credit available</option>
                        <option value="Group projects">Group projects</option>
                        <option value="Good Instructor">Good Instructor</option>
                        <option value="Easy A">Easy A</option>
                        <option value="Provides Feedback">Provides Feedback</option>
                        <option value="Test heavy">Test heavy</option>
                        <option value="Pop quizzes">Pop quizzes</option>
                    </select>
                </td></tr>';

        echo '<tr><td colspan="2">
                <input type="hidden" name="student_id" value="' . htmlspecialchars($student_id) . '">
                <button type="submit">Submit Rating</button>
              </td></tr>
              </table></form>';
    } else {
        echo "No courses available.";
    }
}
$conn->close();
?>