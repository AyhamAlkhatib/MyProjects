<?php
// Fetch the student_id from the URL query string
$student_id = isset($_GET['student_id']) ? $_GET['student_id'] : null;
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Student Page</title>
</head>
<body>
    <h1>Welcome, Student!</h1>

    <table border="1">
        <tr>
            <td>
                <form action="course_history_GPA.php" method="post">
                    <input type="hidden" name="student_id" value="<?php echo htmlspecialchars($student_id); ?>">
                    <button type="submit">View previous courses & cumulative GPA</button>
                </form>
            </td>
        </tr>
        <tr>
            <td>
                <form action="fill_information.php" method="post">
                    <input type="hidden" name="student_id" value="<?php echo htmlspecialchars($student_id); ?>">
                    <button type="submit">Modify My Information</button>
                </form>
            </td>
        </tr>
        <tr>
            <td>
            <form action="show_courses_4registration.php" method="post">
                <input type="hidden" name="student_id" value="<?php echo htmlspecialchars($student_id); ?>">
                <button type="submit">Browse Courses & Enroll</button>
            </form>
            </td>
        </tr>
        <tr>
            <td>
                <form action="show_courses_enrolled_2withdraw.php" method="post">
                    <input type="hidden" name="student_id" value="<?php echo htmlspecialchars($student_id); ?>">
                    <button type="submit">Withdraw from a course</button>
                </form>
            </td>
        </tr>
        <tr>
            <td>
                <form action="rate_instructor_info.php" method="post">
                    <input type="hidden" name="student_id" value="<?php echo htmlspecialchars($student_id); ?>">
                    <button type="submit">Rate a previous Instructor</button>
                </form>
            </td>
        </tr>
        <tr>
            <td>
                <form action="see_ratings.php" method="post">
                    <input type="hidden" name="student_id" value="<?php echo htmlspecialchars($student_id); ?>">
                    <button type="submit">See Ratings</button>
                </form>
            </td>
        </tr>
        <tr>
            <td>
                <form action="main.html" method="post">
                    <button type="submit">Sign Out</button>
                </form>
            </td>
        </tr>
    </table>
</body>
</html>