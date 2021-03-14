<!-- This page is loaded into resolveCorrelations.php using jQuery's load() function -->
<div class="row">
<?php

require('common_functions.php');

function copy_mapping_controls($sql_conn, $prefix, $srcBank, $srcDesc, $book_id) {
	// generate some controls for creating a mapping
	echo "<div id=\"".$prefix."Container\">";
	echo "<div>";
	echo "Source Bank account linked to: ";
	make_account_with_type_dropdown($sql_conn, $prefix."SrcBankAccountLink", $book_id);
	echo "</div>";	
	echo "<div>";
	echo "With line type: ";
	make_line_type_dropdown($sql_conn, $prefix."SrcBankLineType");
	echo "</div>";

	echo "<div>";
	echo "Description linked to: ";
	make_account_with_type_dropdown($sql_conn, $prefix."DstAccountLink", $book_id);
	echo "</div>";	
	echo "<div>";
	echo "With line type: ";
	make_line_type_dropdown($sql_conn, $prefix."DstLineType");
	echo "</div>";

	echo "<button type=\"button\" class=\"btn btn-info\" onclick=\"doMap('".$prefix."');\">Map</button>";
	echo "</div>";
}

?>
	<div class="col-12">
		<h5>Unresolved correlations list</h5>
		<table class="table">
		<tr>
			<th>Source Bank Account</th>
			<th>Description</th>
			<th># transactions</th>
			<th>Enter mapping info:</th>
		</tr>
		<?php
		
		//select upload data records with no matching mappings
		$cor_query = "select imp.src_bank_account, imp.description, count(*) as cnt from imported_data as imp left join correlations_table as ct on imp.src_bank_account = ct.src_bank_account and imp.description = ct.dst_description where ct.correlation_id is null group by imp.src_bank_account, imp.description order by count(*) desc;";

		/////	echo "<div>".$cor_query."</div>";

		$conn = new mysqli("localhost", "free_budget_conn", "badpassword", "free_budget_db");
		if (mysqli_connect_error()) {
			die("Failed to connect to db: " . mysqli_connect_error());
		}
		try {
			$book_id = "1"; //TODO how to get this?
			$sel = $conn->query($cor_query);
			$ctr = 0;
			while($row = $sel->fetch_assoc()) {
				$this_prefix = "mapping".$ctr;
				echo "<tr>";
				echo "<td style=\"width: 15%\" id=\"".$this_prefix."SrcBankAccount\">";
				echo "".$row["src_bank_account"]."";
				echo "</td>";
				echo "<td style=\"width: 18%\" id=\"".$this_prefix."Description\">";
				echo "".$row["description"]."";
				echo "</td>";
				echo "<td style=\"width: 10%\">";
				echo "".$row["cnt"]."";
				echo "</td>";
				echo "<td>";
				copy_mapping_controls($conn, $this_prefix, $row["src_bank_account"], $row["description"], $book_id);
				echo "</td>";
				echo "<tr>";
				$ctr++;
			}
		} catch(Exception $e) {
			echo "Error getting list of unresolved correlations: " . $e->getMessage();
		}
		?>
		</table>
		
	</div>
</div>

