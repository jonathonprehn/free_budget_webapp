#!/usr/bin/ruby 

# versions of ruby libraries to connect
# dbd-mysql (0.4.4)
# dbi (0.4.5)
# mysql (2.9.1)

require "dbi"

print "Content-Type:application/json\n\n"

begin
	dbh = DBI.connect("DBI:Mysql:free_budget_db:localhost", "free_budget_conn", "badpassword")
	sel_stmt = "select transaction_date,imp.src_bank_account,imp.description,amount,src_line_type_id,dst_line_type_id,src_account_id,dst_account_id,upload_date from imported_data as imp left join correlations_table as ct on imp.src_bank_account = ct.src_bank_account and imp.description = ct.dst_description left join uploaded_files as uf on imp.upload_id = uf.upload_id where imp.correlated_flag <> b'1' or imp.correlated_flag is null;"
	
	book_id = "1" # TODO: How to get?
	entry_id = 1
	entry_id_sel = dbh.prepare("select ifnull(max(entry_id)+1, 1) as nextID from accounting_entries;")
	entry_id_sel.execute
	entry_id_sel.fetch do |row|
		entry_id = row["nextID"].to_i
	end

	# puts "entry_id = '#{entry_id}'"
	# if entry_id.nil?
	# 	puts "Entry id returned as nil for some reason"
	# 	return
	# end
	

	insert_entry_stmt = "insert into accounting_entries (entry_id, rel_book_id, entered) values (?,?,?);"
	insert_line_stmt = "insert into accounting_lines (rel_accounting_entry_id, rel_account_id, rel_line_type_id, amount, memo) values (?,?,?,?,?);"
	
	sth = dbh.prepare(sel_stmt)
	entry_inserter = dbh.prepare(insert_entry_stmt)
	line_inserter = dbh.prepare(insert_line_stmt)

	count_mapped = 0	
	sth.execute
	sth.fetch do |row|
		# ensure that everything isn't null
		entry_inserter.execute(entry_id, book_id, row[8])
		line_inserter.execute(entry_id, row[6], row[4], row[3], row[1]) # src bank account line
		line_inserter.execute(entry_id, row[7], row[5], row[3], row[2]) # dst description
		entry_id = entry_id + 1
		count_mapped = count_mapped + 1
	end
	
	line_inserter.finish
	entry_inserter.finish
	sth.finish

	# update the correlations that had matches, and flag them as correlated
	update_correlate = "update imported_data left join correlations_table on imported_data.src_bank_account = correlations_table.src_bank_account and imported_data.description = correlations_table.dst_description set imported_data.correlated_flag = b'1' where imported_data.correlated_flag <> b'1' or imported_data.correlated_flag is null;" 
	update_sth = dbh.prepare(update_correlate)
	update_sth.execute
	update_sth.finish

	dbh.commit
	print "{ \"msg\": \"successfully mapped #{count_mapped}\" }"
rescue DBI::DatabaseError => e    
	print "{ \"error\": \"#{e.err}; #{e.errstr}\" }"
	dbh.rollback
ensure
	dbh.disconnect if dbh
end

