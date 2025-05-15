<!DOCTYPE html>
<html>
<head>
    <title>Show Courses</title>
</head>
<body>
    <h1>Select Course</h1>
    
    <form action="show_sections_4course_registeration.php" method="post">
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
                            // FETCHES the course name, id and puts them as a value to be selected by the student
                            $result = $conn->query("SELECT course_name, course_id FROM course");

                            // Check if any courses are returned
                            if ($result->num_rows > 0) {
                                while ($row = $result->fetch_assoc()) {
                                    echo '<option value="' . $row['course_id'] . '">' . $row['course_id'] . ' - ' . $row['course_name'] . '</option>';
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
                    <!-- Sends the student id to the backend as a hidden value -->
                    <input type="hidden" name="student_id" value="<?php echo isset($student_id) ? htmlspecialchars($student_id) : ''; ?>">
                </td>
            </tr>
        </table>
        <br><br>
        <!-- Select Semester by putting them as a value in a dropdown button -->            
        <label for="semester">Select Semester:</label>
        <select name="semester" id="semester" required>
            <option value="Spring">Spring</option>
            <option value="Summer">Summer</option>
            <option value="Fall">Fall</option>
            <option value="Winter">Winter</option>
        </select>
        <br><br>
        
        <!-- Select year by putting them as a value in a dropdown button -->
        <label for="year">Select Year:</label>
        <select name="year" id="year" required>
            <?php 
            for ($year = 1990; $year <= 2100; $year++) {
                echo "<option value=\"$year\">$year</option>";
            }
            ?>
        </select>
        <br><br>

        <button type="submit">Show Sections!</button>

    </form>
</body>
</html>

