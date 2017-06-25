-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: May 03, 2017 at 08:38 AM
-- Server version: 5.5.55-0ubuntu0.14.04.1
-- PHP Version: 5.5.9-1ubuntu4.21

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `plan_calendar`
--

-- --------------------------------------------------------

--
-- Table structure for table `calendar`
--

CREATE TABLE IF NOT EXISTS `calendar` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `name` varchar(255) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user_id` (`user_id`,`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `event`
--

CREATE TABLE IF NOT EXISTS `event` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `parent_id` int(11) DEFAULT NULL,
  `status` int(11) NOT NULL DEFAULT '1' COMMENT '1 - povinny, 2 - volitelny, 3 - presouvatelny',
  `public` tinyint(1) NOT NULL DEFAULT '1' COMMENT '1 - soukroma, 2 - verejna, 3 - sdilena',
  `name` varchar(512) COLLATE utf8_bin NOT NULL,
  `description` text COLLATE utf8_bin,
  `repeatable` tinyint(4) DEFAULT '0' COMMENT 'opakovani - 1 - ano, 0 - ne',
  `repeat_const` double DEFAULT '0' COMMENT 'Opakovat po - casovy interval v hod',
  `repeat_count` int(11) DEFAULT '0' COMMENT 'Kolikrat se bude opakovat, nekonecno = -1',
  `calendar_id` int(11) NOT NULL,
  `datetime_start` datetime NOT NULL,
  `datetime_end` datetime DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `datetime_start` (`datetime_start`,`calendar_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `lifestyle`
--

CREATE TABLE IF NOT EXISTS `lifestyle` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `value` varchar(255) COLLATE utf8_bin NOT NULL,
  `time_start` time NOT NULL,
  `time_end` time NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=5 ;

--
-- Dumping data for table `lifestyle`
--

INSERT INTO `lifestyle` (`id`, `value`, `time_start`, `time_end`) VALUES
(1, 'Breakfast', '07:00:00', '07:30:00'),
(2, 'Lunch', '12:00:00', '12:30:00'),
(3, 'Snack', '16:00:00', '16:15:00'),
(4, 'Dinner', '19:00:00', '19:30:00');

-- --------------------------------------------------------

--
-- Table structure for table `shared_events`
--

CREATE TABLE IF NOT EXISTS `shared_events` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `owner_id` int(11) NOT NULL COMMENT 'Vlastnik udalosti',
  `shared_id` int(11) NOT NULL COMMENT 'S kym udalost sdili',
  `calendar_id` int(11) NOT NULL COMMENT 'ID udalosti',
  PRIMARY KEY (`id`),
  UNIQUE KEY (`owner_id`, `shared_id`, `calendar_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE IF NOT EXISTS `user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_bin NOT NULL,
  `password` varchar(512) COLLATE utf8_bin NOT NULL,
  `name` varchar(255) COLLATE utf8_bin NOT NULL,
  `surname` varchar(255) COLLATE utf8_bin NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=1 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
