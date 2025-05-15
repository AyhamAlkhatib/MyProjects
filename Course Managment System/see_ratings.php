<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "DB2";

// Connect
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>View Professor Ratings</title>
</head>
<body>
    <h1>View Professor Ratings by Course</h1>

    <!-- Course Selection Form -->
    <form method="post">
        <label for="course_id">Select a Course:</label>
        <select name="course_id" id="course_id" required>
            <option value="">-- Choose a Course --</option>
            <?php
            // Fetch available courses from the course table
            $course_result = $conn->query("SELECT course_id, course_name FROM course");
            if ($course_result->num_rows > 0) {
                while ($row = $course_result->fetch_assoc()) {
                    echo '<option value="' . $row['course_id'] . '">' . $row['course_id'] . ' - ' . $row['course_name'] . '</option>';
                }
            } else {
                echo '<option value="">No courses found</option>';
            }
            ?>
        </select>
        <button type="submit">View Ratings</button>
    </form>

    <?php
    // If form submitted, display ratings
    if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['course_id']) && $_POST['course_id'] !== '') {
        $selected_course_id = $_POST['course_id'];
        echo "<h2>Ratings for Course: $selected_course_id</h2>";

        $rating_query = "SELECT instructor_name, quality, difficulty, take_again, for_credit, attendance, tags
                         FROM rating
                         WHERE course_id = '$selected_course_id'";
        $ratings = $conn->query($rating_query);

        if ($ratings->num_rows > 0) {
            echo "<table border='1' cellpadding='5'>
                    <tr>
                        <th>Instructor</th>
                        <th>Quality</th>
                        <th>Difficulty</th>
                        <th>Take Again</th>
                        <th>For Credit</th>
                        <th>Attendance</th>
                        <th>Tags</th>
                    </tr>";
            while ($row = $ratings->fetch_assoc()) {
                echo "<tr>
                        <td>{$row['instructor_name']}</td>
                        <td>{$row['quality']}</td>
                        <td>{$row['difficulty']}</td>
                        <td>{$row['take_again']}</td>
                        <td>{$row['for_credit']}</td>
                        <td>{$row['attendance']}</td>
                        <td>{$row['tags']}</td>
                      </tr>";
            }
            echo "</table>";
        } else {
            echo "<p>No ratings found for this course.</p>";
        }
    }

    $conn->close();
    ?>
</body>
</html>