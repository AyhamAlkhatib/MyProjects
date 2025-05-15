<!DOCTYPE html>
<html lang="en">
<head>
    <title>Assign Grader</title>
</head>
<body>
    <h1>Select Course</h1>

    <form action="show_grader.php" method="post">
        <table border="1" cellpadding="10" cellspacing="0">
            <tr>
                <td><label for="course_id"><strong>Course ID:</strong></label></td>
                <td>
                    <select name="course_id" id="course_id" required>
                        <?php
                        $servername = "localhost";
                        $username = "root";
                        $password = "";
                        $dbname = "DB2";

                        // Establish connection
                        $conn = new mysqli($servername, $username, $password, $dbname);

                        // Check connection
                        if ($conn->connect_error) {
                            die("Connection failed: " . $conn->connect_error);
                        }

                        // Query to fetch courses
                        $result = $conn->query("SELECT course_id, course_name FROM course");

                        // Check if any courses exist, if it exists then display the course id and name
                        if ($result->num_rows > 0) {
                            echo '<option value="" disabled selected>-- Select a Course --</option>';
                            while ($row = $result->fetch_assoc()) {
                                echo '<option value="' . $row['course_id'] . '">' . $row['course_name'] . ' (ID: ' . $row['course_id'] . ')</option>';
                            }
                        } else {
                            echo '<option value="" disabled>No courses available</option>';
                        }

                        $conn->close();
                        ?>
                    </select>
                </td>
            </tr>
            <tr>
                <td colspan="2" align="center">
                    <button type="submit"><strong>Find Graders!</strong></button>
                </td>
            </tr>
        </table>
    </form>
</body>
</html>