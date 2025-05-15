<!DOCTYPE html>
<html>
<head>
    <title>Show Courses</title>
</head>
<body>
    <h1>Select Course</h1>

    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['course_id']) && isset($_POST['section_id'])) {
        echo "course_id: " . $_POST['course_id'] . ", section_id: " . $_POST['section_id'] . "<br>";
    }
    ?>

    <form action="withdraw_course.php" method="post">
        <table border="1">
            <tr>
                <td><label for="course_id">Course ID:</label></td>
                <td>
                    <select name="course_id" id="course_id" required>
                        <?php
                        $servername = "localhost";
                        $username = "root";
                        $password = "";
                        $dbname = "DB2";

                        $conn = new mysqli($servername, $username, $password, $dbname);

                        if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['student_id'])) {
                            $student_id = $_POST['student_id'];

                            $result = $conn->query("SELECT course_id, section_id, grade FROM take WHERE student_id = '$student_id'");

                            if ($result->num_rows > 0) {
                                while ($row = $result->fetch_assoc()) {
                                    $grade = $row['grade'];
                                    if (empty($grade)) {
                                        echo "<option value='" . $row['course_id'] . "'>" . $row['course_id'] . "</option>";
                                        // Store section_id as hidden field for now
                                        echo "<input type='hidden' name='section_id' value='" . $row['section_id'] . "'>";
                                    }
                                }
                            } else {
                                echo '<option value="">No courses available</option>';
                            }
                        }

                        $conn->close();
                        ?>
                    </select>
                </td>
            </tr>
            <tr>
                <td colspan="2">
                    <input type="hidden" name="student_id" value="<?php echo isset($student_id) ? htmlspecialchars($student_id) : ''; ?>">
                </td>
            </tr>
            <tr>
                <td colspan="2">
                    <button type="submit">Withdraw from Course</button>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>