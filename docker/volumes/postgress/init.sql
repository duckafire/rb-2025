/*
Original file:
	https://github.com/zanfranceschi/rinha-de-backend-2025/blob/main/payment-processor/init.sql

WAL - Write Ahead-Log: modifications are written in a log file
                       before to be written in a table, this
                       easily the recovery of the data after
                       crashes, shutdowns and similar.

INLOGGED TABLE : do not use the WAL algorithm, so it is fastest.
UUID : Universal Unique IDentifier

*/

CREATE UNLOGGED TABLE payments (
    correlationId UUID      PRIMARY KEY,
    amount        DECIMAL   NOT NULL,
    requested_at  TIMESTAMP NOT NULL
);

CREATE INDEX payments_requested_at ON payments (requested_at);
