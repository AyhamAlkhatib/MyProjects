<?php
$servername = "localhost";
$username = "root";
$password = ""; 
$dbname = "DB2"; 

$conn = new mysqli($servername, $username, $password, $dbname);

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $student_id = (string) $_POST['student_id'];
    $instructor_id = (string) $_POST['instructor_id'];

    // Fetch courses taken by the student
    $student_courses = $conn->query("SELECT course_id FROM take WHERE student_id = '$student_id'");
    $total_credits = 0;
    $total_grade_points = 0;

    // Grade values mapping
    $grade_values = [
        'A+' => 4.0, 'A' => 4.0, 'A-' => 3.7, 'B+' => 3.3, 
        'B' => 3.0, 'B-' => 2.7, 'C+' => 2.3, 'C' => 2.0, 
        'C-' => 1.7, 'D+' => 1.3, 'D' => 1.0, 'D-' => 0.7, 'F' => 0.0
    ];

    // Prepare for displaying course details
    $course_details = [];

    while ($row = $student_courses->fetch_assoc()) {
        $student_course = $row['course_id'];

        // Fetch course details (credits and grade)
        $course_credit = $conn->query("SELECT credits FROM course WHERE course_id = '$student_course'");
        $sql_letter_grade = $conn->query("SELECT grade FROM take WHERE student_id = '$student_id' AND course_id = '$student_course'");

        $course_credit_result = $course_credit->fetch_assoc();
        $course_credit_result = $course_credit_result['credits'];

        $letter_grade_result = $sql_letter_grade->fetch_assoc();
        $grade = $letter_grade_result['grade'];

        // Add course details and calculate grade points
        if (array_key_exists($grade, $grade_values)) {
            $course_details[] = [
                'course_id' => $student_course,
                'grade' => $grade,
                'credits' => $course_credit_result
            ];
            // Accumulate total grade points and credits for GPA calculation
            $total_grade_points += $grade_values[$grade] * $course_credit_result;
            $total_credits += $course_credit_result;
        }
    }

    // Calculate GPA
    if ($total_credits > 0) {
        $gpa = $total_grade_points / $total_credits;
    } else {
        $gpa = null;
    }
}
$conn->close();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Student GPA</title>
</head>
<body>

    <h2>Student Course Details</h2>

    <?php if (isset($course_details) && !empty($course_details)): ?>
        <table border="1" cellpadding="10" cellspacing="0">
            <tr>
                <th>Course ID</th>
                <th>Grade</th>
                <th>Credits</th>
            </tr>
            <?php foreach ($course_details as $course): ?>
                <tr>
                    <td><?php echo $course['course_id']; ?></td>
                    <td><?php echo $course['grade']; ?></td>
                    <td><?php echo $course['credits']; ?></td>
                </tr>
            <?php endforeach; ?>
        </table>

        <h3>Total Credits: <?php echo $total_credits; ?></h3>
        <h3>GPA: <?php echo $gpa !== null ? number_format($gpa, 2) : 'No valid courses to calculate GPA.'; ?></h3>
    <?php else: ?>
        <p>No courses found for the given student ID.</p>
    <?php endif; ?>

    <a href="instructor_main_page.php?instructor_id=<?php echo $instructor_id; ?>"><button>Instructor Main Page</button></a>

</body>
</html>