-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 24, 2023 at 07:52 PM
-- Server version: 10.4.25-MariaDB
-- PHP Version: 8.1.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `pinnacle`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin_table`
--

CREATE TABLE `admin_table` (
  `NO` int(255) DEFAULT NULL,
  `admin_id` varchar(10) NOT NULL,
  `admin_name` varchar(50) NOT NULL,
  `admin_ic` varchar(12) NOT NULL,
  `admin_address` varchar(210) NOT NULL,
  `admin_phone` varchar(11) NOT NULL,
  `admin_pwd` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `admin_table`
--

INSERT INTO `admin_table` (`NO`, `admin_id`, `admin_name`, `admin_ic`, `admin_address`, `admin_phone`, `admin_pwd`) VALUES
(NULL, 'winnie23', 'winnie', '710723105890', '123', '0166740274', 'winnie23');

-- --------------------------------------------------------

--
-- Table structure for table `booking_table`
--

CREATE TABLE `booking_table` (
  `NO` int(11) NOT NULL,
  `booking_id` varchar(10) NOT NULL,
  `court_id` varchar(5) NOT NULL,
  `mem_id` varchar(10) DEFAULT NULL,
  `start_time` time DEFAULT NULL,
  `end_time` time DEFAULT NULL,
  `time_stamp` varchar(3) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `booking_table`
--

INSERT INTO `booking_table` (`NO`, `booking_id`, `court_id`, `mem_id`, `start_time`, `end_time`, `time_stamp`) VALUES
(1, 'b1', 'c1', 'herish23', '10:00:00', '11:00:00', 't1'),
(17, 'B17', 'c1', 'dell', '19:00:00', '20:00:00', 't10'),
(19, 'B18', 'c1', 'herish23', '21:00:00', '22:00:00', 't12'),
(20, 'B20', 'c2', 'herish23', '21:00:00', '22:00:00', 't12'),
(21, 'B21', 'c1', 'winnie23', '14:00:00', '15:00:00', 't5'),
(22, 'B22', 'c1', 'herish23', '15:00:00', '16:00:00', 't6'),
(23, 'B23', 'c1', 'herish23', '16:00:00', '17:00:00', 't7'),
(24, 'B24', 'c2', 'herish23', '10:00:00', '11:00:00', 't1'),
(27, 'B25', 'c2', 'rames7', '11:00:00', '12:00:00', 't2'),
(28, 'B28', 'c2', 'niba', '12:00:00', '13:00:00', 't3'),
(16, 'B3', 'c1', 'herish23', '20:00:00', '21:00:00', 't11'),
(30, 'B30', 'c1', '123', '16:00:00', '17:00:00', 't7'),
(31, 'B31', 'c1', '123', '18:00:00', '19:00:00', 't9'),
(33, 'B32', 'c1', 'herish23', '10:00:00', '11:00:00', 't1'),
(34, 'B34', 'c1', 'tima', '11:00:00', '12:00:00', 't2'),
(35, 'B35', 'c1', 'tima', '12:00:00', '13:00:00', 't3'),
(36, 'B36', 'c1', 'herish23', '21:00:00', '22:00:00', 't12'),
(37, 'B37', 'c1', 'herish23', '19:00:00', '20:00:00', 't10'),
(43, 'B38', 'c1', 'herish23', '10:00:00', '11:00:00', 't1'),
(44, 'B44', 'c1', 'tima', '11:00:00', '12:00:00', 't2'),
(57, 'B57', 'c1', 'herish23', '13:00:00', '14:00:00', 't4'),
(58, 'B58', 'c1', 'herish23', '14:00:00', '15:00:00', 't5'),
(59, 'B59', 'c1', 'herish23', '15:00:00', '16:00:00', 't6'),
(60, 'B60', 'c1', 'shiwaani07', '14:00:00', '15:00:00', 't5'),
(61, 'B61', 'c3', 'herish23', '11:00:00', '12:00:00', 't2');

-- --------------------------------------------------------

--
-- Table structure for table `court_table`
--

CREATE TABLE `court_table` (
  `court_id` varchar(5) NOT NULL,
  `court_num` varchar(20) NOT NULL,
  `court_avail` varchar(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `court_table`
--

INSERT INTO `court_table` (`court_id`, `court_num`, `court_avail`) VALUES
('c1', '1', 'A'),
('c2', '2', 'A'),
('c3', '3', 'A');

-- --------------------------------------------------------

--
-- Table structure for table `member_table`
--

CREATE TABLE `member_table` (
  `mem_id` varchar(10) NOT NULL,
  `mem_name` varchar(50) NOT NULL,
  `mem_ic` varchar(12) NOT NULL,
  `mem_address` varchar(210) NOT NULL,
  `mem_phone` varchar(11) NOT NULL,
  `mem_pwd` varchar(10) NOT NULL,
  `mem_start_date` date NOT NULL,
  `mem_end_date` date NOT NULL,
  `mem_points` bigint(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `member_table`
--

INSERT INTO `member_table` (`mem_id`, `mem_name`, `mem_ic`, `mem_address`, `mem_phone`, `mem_pwd`, `mem_start_date`, `mem_end_date`, `mem_points`) VALUES
('123', 'asdasd', '123456789012', '12', '1234567890', '12345678', '2023-01-11', '2023-01-20', 200),
('ari23', 'ARIANNA GRANDE', '021223100804', 'BEVERLY ', '0106680274', 'arianna1', '2023-01-11', '2024-01-10', 0),
('dddd', '11', '123456789098', '12', '1234567890', 'dddd1234', '2023-01-11', '2024-01-10', 0),
('dell', 'DELL', '123456789012', 'JASDSD', '1234567890', 'dell1234', '2023-01-11', '2024-01-10', 70),
('dert1234', '121212', '123456789098', '12', '1234567890', 'dert1234', '2023-01-11', '2024-01-10', 0),
('dylanmu', 'akjsdkasd', '123456765432', '12132', '1234321234', 'dylan123', '2022-10-17', '2024-01-16', 0),
('genius', '1122', '123456789098', '12', '1234567890', 'genius12', '2023-01-11', '2024-01-10', 0),
('gongcha', 'GONG CHA', '123456789098', '123456', '1234567890', 'gongcha1', '2022-10-17', '2024-01-16', 0),
('herish12', 'QQ', '123456789012', '123123123', '1234567890', 'herish12', '2023-01-11', '2024-01-10', 0),
('herish23', 'HERISH', '021223100803', 'SDSAS', '0166740274', 'herish22', '2023-01-11', '2024-01-10', 300),
('hijau', 'hilap', '021223100908', '123', '0166740253', 'jinjong1', '2022-10-17', '2024-01-16', 0),
('hijaukli', 'sadsdasd', '123212343212', '123', '12332123432', 'klmmg123', '2022-10-17', '2024-01-16', 0),
('hublot', 'saad', '123456789098', '12', '1234567890', 'hublot12', '2023-01-11', '2024-01-10', 0),
('keertik07', 'KEERTIK CHAUDDRAY', '001117100748', 'NO4 JALAN SP5/9 TAMAN SUJANA PUCHONG', '0102110364', 'keertik1', '2022-10-20', '2024-01-19', 0),
('kilau', 'alajshdas', '123456543212', '12', '1234321234', 'kilat123', '2022-10-17', '2024-01-16', 0),
('kilop', 'asdasd', '123454321234', '123', '1234532123', 'pilopi12', '2022-10-17', '2024-01-16', 0),
('ku', 'asasd', '123456789098', '12', '1234567890', 'ku123456', '2023-01-11', '2024-01-10', 0),
('lopi12', 'akdgasd', '123212343212', '123', '1234321234', 'lopi1234', '2022-10-17', '2024-01-16', 0),
('lopik', 'mikeler', '123456789098', '123', '1233211234', 'lopik123', '2022-10-17', '2024-01-16', 0),
('lumfu', 'LUM FU YUAN ', '021223100809', 'NO 4 JALAN TEPI PADANG ', '0199985217', 'lumfu123', '2024-10-20', '2024-01-19', 100),
('makai', '12121', '123456543212', '12', '1234321234', 'makai123', '2022-10-17', '2024-01-16', 0),
('matkialu', 'MAT KILAU BIN BAKAR', '990013108764', 'JALAN TELAWI 13', '0166740276', 'kilau123', '2022-10-17', '2024-01-16', 0),
('mikala', 'DYLAN ', '041223198121', 'poiik', '1234543212', 'mikala12', '2022-10-17', '2024-01-16', 0),
('mikel', 'MIKEL', '123456789098', '123', '1234567890', 'mikel121', '2022-10-17', '2024-01-16', 0),
('minu', 'adasdasd', '123456789098', '12', '1234567890', 'minu1234', '2023-01-11', '2024-01-10', 0),
('niba', 'juk', '021223100803', '12', '0189997654', 'nibba123', '2022-10-17', '2024-01-16', 100),
('piranha', 'ASDASDAS', '123432123454', '12', '1234321234', 'piran123', '2022-10-17', '2024-01-16', 0),
('poi', '1212', '123456789012', '123456789', '1234567890', '12345678', '2023-01-11', '2024-01-10', 0),
('poll', 'QW', '123456789009', '12', '1234567890', 'poll1234', '2023-01-11', '2024-01-10', 0),
('poyi', 'ASDASD', '123454321234', '123', '1234565432', 'poyi1234', '2022-10-20', '2024-01-19', 0),
('qi', 'ppp', '123456789012', '12', '1234567890', '12345678', '2023-01-11', '2024-01-10', 0),
('qw', 'asdsdd', '123456789012', '1313', '1234567890', 'qwqwqwqw', '2023-01-11', '2024-01-10', 0),
('qwerty', 'adajasdasd', '123456789012', 'qq', '1234567890', 'qwertyui', '2023-01-11', '2024-01-10', 0),
('rames7', 'RAMES', '021223100809', 'TAMING SARI TERAS', '0137789654', 'rames123', '2022-10-17', '2024-01-16', 100),
('ravi', 'akjdgasd', '123454321234', '123', '1234543212', 'ravi1234', '2022-10-17', '2024-01-16', 0),
('razi', 'razi', '123456789098', '123', '1234567890', 'razi1234', '2022-10-17', '2024-01-16', 0),
('roshini08', 'ROSHINI', '021008070592', 'SDAHASD', '01133040274', 'roshini8', '2023-01-11', '2024-01-10', 0),
('roshini230', 'ROSHINI RAMES', '021008070592', 'NO 23 LORONG TANJUNG 6 P.PINANG', '01133040274', 'roshini8', '2022-10-20', '2024-01-19', 0),
('roshini7', 'ROSHINI RAMES', '021008070592', 'NO 23 TAMAN MUTIARA PP', '01133040274', 'roshini7', '2022-10-20', '2024-01-19', 0),
('sasa', 'sasa', '123456789012', '12', '1234567890', 'sasa1234', '2023-01-11', '2024-01-10', 0),
('shiwaani07', 'SHIWAANI ', '021223100803', 'NO 4 JALAN TAMING SARI ', '0189985217', 'shiwaani', '2023-10-20', '2024-01-19', 100),
('sigma12', 'KALAIVENI AP ALAGESU', '710723100803', 'NO 4 JLN TAMING SARI', '0166740274', 'sigma123', '2022-10-20', '2024-01-19', 0),
('thor', 'askhdgaksd', '123456789098', '12132', '1234567890', 'thor1234', '2022-10-17', '2024-01-16', 0),
('tima', 'TIMA', '123456789012', 'NSADKSD', '1234567890', 'tima1234', '2022-10-17', '2024-01-16', 1210),
('tt', 'sadsd', '123123212313', 'sdasdasdd', '12123123123', 'tttttttt', '2023-01-11', '2024-01-10', 0),
('winnie23', 'winnie', '710723105890', 'kkk', '0166740274', 'winnie23', '2023-01-11', '2024-01-10', 100),
('winnie2312', 'asdasda', '123456789098', '12', '1234567890', 'kilalala', '2023-01-11', '2024-01-10', 0);

-- --------------------------------------------------------

--
-- Table structure for table `payment_table`
--

CREATE TABLE `payment_table` (
  `NO` int(11) NOT NULL,
  `payment_id` varchar(10) NOT NULL,
  `booking_id` varchar(10) DEFAULT NULL,
  `register_id` varchar(10) DEFAULT NULL,
  `amount` float NOT NULL,
  `payment_date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `payment_table`
--

INSERT INTO `payment_table` (`NO`, `payment_id`, `booking_id`, `register_id`, `amount`, `payment_date`) VALUES
(1, 'p1', NULL, 'R1', 500, '2022-12-09'),
(17, 'P10', '', 'R10', 500, '2022-11-09'),
(18, 'P11', '', 'R11', 500, '2023-01-09'),
(19, 'P12', '', 'R12', 500, '2023-01-09'),
(21, 'P13', '', 'R13', 500, '2023-01-09'),
(26, 'P18', '', 'R18', 500, '2023-01-09'),
(2, 'P2', '', 'R3', 500, '2023-01-09'),
(20, 'P20', 'B20', '', 70, '2023-01-16'),
(29, 'P21', NULL, 'R21', 500, '2023-01-09'),
(34, 'P22', NULL, 'R22', 500, '2022-10-17'),
(36, 'P23', NULL, 'R23', 350, '2023-02-15'),
(37, 'P24', NULL, 'R24', 500, '2022-10-17'),
(38, 'P25', NULL, 'R25', 500, '2022-10-17'),
(39, 'P26', NULL, 'R26', 500, '2022-10-17'),
(40, 'P27', NULL, 'R27', 500, '2022-10-17'),
(41, 'P28', NULL, 'R28', 500, '2022-10-17'),
(42, 'P29', NULL, 'R29', 500, '2022-10-17'),
(30, 'P30', 'B21', NULL, 70, '2023-01-16'),
(31, 'P31', 'B22', NULL, 70, '2023-01-16'),
(32, 'P32', 'B23', NULL, 0, '2023-01-16'),
(33, 'P33', 'B24', NULL, 70, '2022-10-17'),
(35, 'P35', 'B25', NULL, 70, '2022-10-17'),
(3, 'P4', '', 'R4', 500, '2023-01-09'),
(43, 'P43', 'B28', NULL, 70, '2022-10-17'),
(47, 'P44', NULL, 'R33', 500, '2022-10-17'),
(48, 'P48', NULL, 'R34', 500, '2022-10-17'),
(49, 'P49', NULL, 'R35', 500, '2022-10-17'),
(4, 'P5', '', 'R5', 350, '2023-01-09'),
(50, 'P50', NULL, 'R36', 500, '2022-10-17'),
(51, 'P51', NULL, 'R39', 350, '2022-10-17'),
(52, 'P52', NULL, 'R40', 350, '2022-10-17'),
(54, 'P54', 'B30', NULL, 70, '2022-10-18'),
(55, 'P55', 'B31', NULL, 70, '2022-10-18'),
(56, 'P56', 'B32', NULL, 70, '2022-10-19'),
(57, 'p57', 'B34', NULL, 80, '2022-10-19'),
(58, 'p58', 'B35', NULL, 80, '2022-10-19'),
(59, 'P59', 'B36', NULL, 70, '2022-10-19'),
(6, 'p6', 'B1', NULL, 70, '2023-01-17'),
(60, 'P60', 'B37', NULL, 70, '2022-10-19'),
(66, 'P61', 'B38', NULL, 70, '2022-10-20'),
(67, 'p67', 'B44', NULL, 80, '2022-10-20'),
(69, 'P69', NULL, 'R41', 350, '2022-10-20'),
(7, 'P7', 'B3', '', 70, '2023-01-09'),
(70, 'P70', NULL, 'R42', 350, '2022-10-20'),
(71, 'P71', NULL, 'R43', 350, '2022-10-20'),
(72, 'P72', NULL, 'R44', 500, '2022-10-20'),
(73, 'P73', NULL, 'R45', 500, '2024-10-20'),
(87, 'P74', NULL, 'R46', 500, '2023-10-20'),
(8, 'p8', 'B17', '', 80, '2023-01-09'),
(88, 'P88', 'B60', NULL, 70, '2023-10-20'),
(89, 'P89', 'B61', NULL, 0, '2023-10-20'),
(10, 'P9', 'B18', '', 70, '2023-01-09');

-- --------------------------------------------------------

--
-- Table structure for table `registration_table`
--

CREATE TABLE `registration_table` (
  `NO` int(11) NOT NULL,
  `register_id` varchar(10) NOT NULL,
  `mem_id` varchar(10) NOT NULL,
  `mem_type` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `registration_table`
--

INSERT INTO `registration_table` (`NO`, `register_id`, `mem_id`, `mem_type`) VALUES
(1, 'R1', 'herish23', 'PLATINUM'),
(10, 'R10', '123', 'PLATINUM'),
(11, 'R11', 'sasa', 'PLATINUM'),
(12, 'R12', 'poi', 'PLATINUM'),
(13, 'R13', 'qi', 'PLATINUM'),
(14, 'R14', 'poll', 'PLATINUM'),
(15, 'R15', 'genius', 'PLATINUM'),
(16, 'R16', 'hublot', 'PLATINUM'),
(17, 'R17', 'dddd', 'PLATINUM'),
(18, 'R18', 'dert1234', 'PLATINUM'),
(19, 'R19', 'winnie2312', 'PLATINUM'),
(2, 'R2', 'roshini08', 'PLATINUM'),
(20, 'R20', 'ku', 'PLATINUM'),
(21, 'R21', 'minu', 'PLATINUM'),
(22, 'R22', 'rames7', 'PLATINUM'),
(23, 'R23', 'tima', 'GOLD'),
(24, 'R24', 'razi', 'PLATINUM'),
(25, 'R25', 'gongcha', 'PLATINUM'),
(26, 'R26', 'mikel', 'PLATINUM'),
(27, 'R27', 'lopik', 'PLATINUM'),
(28, 'R28', 'kilop', 'PLATINUM'),
(29, 'R29', 'niba', 'PLATINUM'),
(3, 'R3', 'winnie23', 'PLATINUM'),
(30, 'R30', 'ravi', 'PLATINUM'),
(31, 'R31', 'hijau', 'PLATINUM'),
(32, 'R32', 'matkialu', 'PLATINUM'),
(33, 'R33', 'makai', 'PLATINUM'),
(34, 'R34', 'kilau', 'PLATINUM'),
(35, 'R35', 'hijaukli', 'PLATINUM'),
(36, 'R36', 'lopi12', 'PLATINUM'),
(37, 'R37', 'thor', 'GOLD'),
(38, 'R38', 'mikala', 'GOLD'),
(39, 'R39', 'dylanmu', 'GOLD'),
(4, 'R4', 'ari23', 'PLATINUM'),
(40, 'R40', 'piranha', 'GOLD'),
(41, 'R41', 'keertik07', 'GOLD'),
(42, 'R42', 'roshini7', 'GOLD'),
(43, 'R43', 'poyi', 'GOLD'),
(44, 'R44', 'sigma12', 'PLATINUM'),
(45, 'R45', 'lumfu', 'PLATINUM'),
(46, 'R46', 'shiwaani07', 'PLATINUM'),
(5, 'R5', 'dell', 'GOLD'),
(8, 'R6', 'qw', 'PLATINUM'),
(9, 'R9', 'qwerty', 'PLATINUM');

-- --------------------------------------------------------

--
-- Table structure for table `staff_table`
--

CREATE TABLE `staff_table` (
  `staff_id` varchar(10) NOT NULL,
  `staff_name` varchar(50) NOT NULL,
  `staff_ic` varchar(12) NOT NULL,
  `staff_address` varchar(210) NOT NULL,
  `staff_phone` varchar(11) NOT NULL,
  `staff_pwd` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `staff_table`
--

INSERT INTO `staff_table` (`staff_id`, `staff_name`, `staff_ic`, `staff_address`, `staff_phone`, `staff_pwd`) VALUES
('rahman', 'rahman', '021223100809', 'JALAN TELAWI 3 ', '0166740274', 'rahman12');

-- --------------------------------------------------------

--
-- Table structure for table `time_table`
--

CREATE TABLE `time_table` (
  `time_stamp` varchar(3) NOT NULL,
  `start_time` time DEFAULT NULL,
  `end_time` time DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `time_table`
--

INSERT INTO `time_table` (`time_stamp`, `start_time`, `end_time`) VALUES
('t1', '10:00:00', '11:00:00'),
('t10', '19:00:00', '20:00:00'),
('t11', '20:00:00', '21:00:00'),
('t12', '21:00:00', '22:00:00'),
('t2', '11:00:00', '12:00:00'),
('t3', '12:00:00', '13:00:00'),
('t4', '13:00:00', '14:00:00'),
('t5', '14:00:00', '15:00:00'),
('t6', '15:00:00', '16:00:00'),
('t7', '16:00:00', '17:00:00'),
('t8', '17:00:00', '18:00:00'),
('t9', '18:00:00', '19:00:00');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin_table`
--
ALTER TABLE `admin_table`
  ADD PRIMARY KEY (`admin_id`);

--
-- Indexes for table `booking_table`
--
ALTER TABLE `booking_table`
  ADD PRIMARY KEY (`booking_id`),
  ADD KEY `NO` (`NO`),
  ADD KEY `booking_table_court_table_FK` (`court_id`),
  ADD KEY `booking_table_member_table_FK` (`mem_id`),
  ADD KEY `booking_table_time_table_FK` (`time_stamp`);

--
-- Indexes for table `court_table`
--
ALTER TABLE `court_table`
  ADD PRIMARY KEY (`court_id`);

--
-- Indexes for table `member_table`
--
ALTER TABLE `member_table`
  ADD PRIMARY KEY (`mem_id`);

--
-- Indexes for table `payment_table`
--
ALTER TABLE `payment_table`
  ADD PRIMARY KEY (`payment_id`),
  ADD KEY `NO` (`NO`),
  ADD KEY `payment_table_booking_table_FK` (`booking_id`),
  ADD KEY `payment_table_registration_table_FK` (`register_id`);

--
-- Indexes for table `registration_table`
--
ALTER TABLE `registration_table`
  ADD PRIMARY KEY (`register_id`),
  ADD KEY `NO` (`NO`),
  ADD KEY `registration_table_member_table_FK` (`mem_id`);

--
-- Indexes for table `staff_table`
--
ALTER TABLE `staff_table`
  ADD PRIMARY KEY (`staff_id`);

--
-- Indexes for table `time_table`
--
ALTER TABLE `time_table`
  ADD PRIMARY KEY (`time_stamp`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `booking_table`
--
ALTER TABLE `booking_table`
  MODIFY `NO` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=62;

--
-- AUTO_INCREMENT for table `payment_table`
--
ALTER TABLE `payment_table`
  MODIFY `NO` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=90;

--
-- AUTO_INCREMENT for table `registration_table`
--
ALTER TABLE `registration_table`
  MODIFY `NO` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=47;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `booking_table`
--
ALTER TABLE `booking_table`
  ADD CONSTRAINT `booking_table_court_table_FK` FOREIGN KEY (`court_id`) REFERENCES `court_table` (`court_id`) ON DELETE CASCADE,
  ADD CONSTRAINT `booking_table_member_table_FK` FOREIGN KEY (`mem_id`) REFERENCES `member_table` (`mem_id`) ON DELETE CASCADE,
  ADD CONSTRAINT `booking_table_time_table_FK` FOREIGN KEY (`time_stamp`) REFERENCES `time_table` (`time_stamp`) ON DELETE CASCADE;

--
-- Constraints for table `payment_table`
--
ALTER TABLE `payment_table`
  ADD CONSTRAINT `payment_table_booking_table_FK` FOREIGN KEY (`booking_id`) REFERENCES `booking_table` (`booking_id`) ON DELETE CASCADE,
  ADD CONSTRAINT `payment_table_registration_table_FK` FOREIGN KEY (`register_id`) REFERENCES `registration_table` (`register_id`) ON DELETE CASCADE;

--
-- Constraints for table `registration_table`
--
ALTER TABLE `registration_table`
  ADD CONSTRAINT `registration_table_member_table_FK` FOREIGN KEY (`mem_id`) REFERENCES `member_table` (`mem_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
