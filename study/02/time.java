package com.shouxin.service.impl;

import cn.hutool.core.date.DateTime;
import cn.hutool.core.date.DateUtil;
import cn.hutool.core.util.StrUtil;
import com.alibaba.druid.sql.visitor.functions.Substring;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.shouxin.dao.PmFwjhMapper;
import com.shouxin.dao.PmXmjhMapper;
import com.shouxin.domain.*;
import com.shouxin.domain.vo.PmFwjhVO;
import com.shouxin.service.*;
import com.shouxin.util.NoGen;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.util.Comparator;
import java.util.Date;
import java.util.List;
import java.util.stream.Collectors;

@Service
@RequiredArgsConstructor
public class PmFwjhServiceImpl extends ServiceImpl<PmXmjhMapper, PmXmjh> implements PmFwjhService {

    private final PmFwjhMapper pmFwjhMapper;
    private final PmXmjhXgfService pmXmjhXgfService;
    private final PmXmjhXzjsjwService pmXmjhXzjsjwService;
    private final PmXmjhYsbzfsService pmXmjhYsbzfsService;
    private final PmXmjhFxjhService pmXmjhFxjhService;
    private final PmXmjhRlzyService pmXmjhRlzyService;
    private final PmXmjhFwbgService pmXmjhFwbgService;
    private final PmXmjhGjzyService pmXmjhGjzyService;
    private final PmXmjhJszcService pmXmjhJszcService;

    @Override
    public Page<PmFwjhVO> queryPage(Page<PmFwjhVO> page, PmFwjhVO pmFwjhVO) {
        QueryWrapper<PmXmjh> queryWrapper = new QueryWrapper<>();

        // 只查询服务计划填报 (1.项目计划填报 2.服务计划填报 3.项目管理单填报)
        queryWrapper.lambda().eq(PmXmjh::getXmjhlx, "2");

        // 项目名称
        if (StrUtil.isNotBlank(pmFwjhVO.getXmmc())) {
            queryWrapper.lambda().like(PmXmjh::getXmmc, pmFwjhVO.getXmmc());
        }

        Page<PmFwjhVO> pmFwjhVOPage = pmFwjhMapper.queryPage(page, queryWrapper);

        // 将8个子表数据放到主表中
        List<PmFwjhVO> pmFwjhVOList = pmFwjhVOPage.getRecords();
        List<PmFwjhVO> collect = pmFwjhVOList.stream().peek(fwjhVO -> {
            // 1.查询服务相关方
            List<PmXmjhXgf> xgfList = pmXmjhXgfService.list(Wrappers.<PmXmjhXgf>lambdaQuery().eq(PmXmjhXgf::getXmjhId, fwjhVO.getId()));
            fwjhVO.setXgf(xgfList);

            // 2.查询限制、假设及界外
            List<PmXmjhXzjsjw> xzjsjwsList = pmXmjhXzjsjwService.list(Wrappers.<PmXmjhXzjsjw>lambdaQuery().eq(PmXmjhXzjsjw::getXmjhId, fwjhVO.getId()));
            fwjhVO.setXzjsjw(xzjsjwsList);

            // 3.查询验收标准和方式
            List<PmXmjhYsbzfs> ysbzfsList = pmXmjhYsbzfsService.list(Wrappers.<PmXmjhYsbzfs>lambdaQuery().eq(PmXmjhYsbzfs::getXmjhId, fwjhVO.getId()));
            fwjhVO.setYsbzfs(ysbzfsList);

            // 4.查询风险计划
            List<PmXmjhFxjh> fxjhList = pmXmjhFxjhService.list(Wrappers.<PmXmjhFxjh>lambdaQuery().eq(PmXmjhFxjh::getXmjhId, fwjhVO.getId()));
            fwjhVO.setFxjh(fxjhList);

            // 5.查询人力资源
            List<PmXmjhRlzy> rlzyList = pmXmjhRlzyService.list(Wrappers.<PmXmjhRlzy>lambdaQuery().eq(PmXmjhRlzy::getXmjhId, fwjhVO.getId()));
            fwjhVO.setRlzy(rlzyList);

            // 6.查询服务报告
            List<PmXmjhFwbg> fwbgList = pmXmjhFwbgService.list(Wrappers.<PmXmjhFwbg>lambdaQuery().eq(PmXmjhFwbg::getXmjhId, fwjhVO.getId()));
            fwjhVO.setFwbg(fwbgList);

            // 7.查询工具资源
            List<PmXmjhGjzy> gjzyList = pmXmjhGjzyService.list(Wrappers.<PmXmjhGjzy>lambdaQuery().eq(PmXmjhGjzy::getXmjhId, fwjhVO.getId()));
            fwjhVO.setGjzy(gjzyList);

            // 8.查询技术支持
            List<PmXmjhJszc> jszcList = pmXmjhJszcService.list(Wrappers.<PmXmjhJszc>lambdaQuery().eq(PmXmjhJszc::getXmjhId, fwjhVO.getId()));
            fwjhVO.setJszc(jszcList);
        }).collect(Collectors.toList());

        pmFwjhVOPage.setRecords(collect);

        return pmFwjhVOPage;
    }

    @Transactional(rollbackFor = Exception.class)
    @Override
    public int addFwjh(PmFwjhVO pmFwjhVO) {
        PmXmjh pmXmjh = new PmXmjh();
        BeanUtils.copyProperties(pmFwjhVO, pmXmjh);

        // 新增服务计划
        // 项目计划类型 (1.项目计划填报 2.服务计划填报 3.项目管理单填报)
        pmXmjh.setXmjhlx("2");
        this.baseMapper.insert(pmXmjh);

        // 1.新增服务相关方
        List<PmXmjhXgf> xgfList = pmFwjhVO.getXgf().stream().peek(pmXmjhXgf -> pmXmjhXgf.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhXgfService.saveBatch(xgfList);

        // 2.新增限制、假设及界外
        List<PmXmjhXzjsjw> xzjsjwsList = pmFwjhVO.getXzjsjw().stream().peek(pmXmjhXzjsjw -> pmXmjhXzjsjw.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhXzjsjwService.saveBatch(xzjsjwsList);

        // 3.新增验收标准和方式
        List<PmXmjhYsbzfs> ysbzfsList = pmFwjhVO.getYsbzfs().stream().peek(pmXmjhYsbzfs -> pmXmjhYsbzfs.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhYsbzfsService.saveBatch(ysbzfsList);

        // 4.新增风险计划
        List<PmXmjhFxjh> fxjhList = pmFwjhVO.getFxjh().stream().peek(pmXmjhFxjh -> {
            QueryWrapper<PmXmjhFxjh> queryWrapper = new QueryWrapper<>();
            List<PmXmjhFxjh> pmXmjhFxjhsList = pmXmjhFxjhService.list(queryWrapper);
            //获取创建时间最新的值
            int num = 0;
            if(!pmXmjhFxjhsList.isEmpty()) {
                PmXmjhFxjh pmXmjhFxjhs = pmXmjhFxjhsList.stream().map(pmXmjhFxjh1 -> {
                    Long timeTemp = pmXmjhFxjh1.getCreatedTime().toInstant(ZoneOffset.of("+8")).toEpochMilli();
                    pmXmjhFxjh1.setRemark10(timeTemp.toString());
                    return pmXmjhFxjh1;
                }).max(Comparator.comparing(pmXmjhFxjh1 -> pmXmjhFxjh1.getRemark10())).get();
                //截取数字
                num = Integer.parseInt(pmXmjhFxjhs.getFxId().substring(2));
            }
            //调用风险id生成规则
            String str = NoGen.getRiskId(num);
            //设置风险id
            pmXmjhFxjh.setFxId(str);
            pmXmjhFxjh.setXmjhId(pmXmjh.getId()); }).collect(Collectors.toList());
        pmXmjhFxjhService.saveBatch(fxjhList);

        // 5.新增人力资源
        List<PmXmjhRlzy> rlzyList = pmFwjhVO.getRlzy().stream().peek(pmXmjhRlzy -> pmXmjhRlzy.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhRlzyService.saveBatch(rlzyList);

        // 6.新增服务报告
        List<PmXmjhFwbg> fwbgList = pmFwjhVO.getFwbg().stream().peek(pmXmjhFwbg -> pmXmjhFwbg.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhFwbgService.saveBatch(fwbgList);

        // 7.新增工具资源
        List<PmXmjhGjzy> gjzyList = pmFwjhVO.getGjzy().stream().peek(pmXmjhGjzy -> pmXmjhGjzy.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhGjzyService.saveBatch(gjzyList);

        // 8.新增技术支持
        List<PmXmjhJszc> jszcList = pmFwjhVO.getJszc().stream().peek(pmXmjhJszc -> pmXmjhJszc.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhJszcService.saveBatch(jszcList);

        return 1;
    }

    @Transactional(rollbackFor = Exception.class)
    @Override
    public int updateFwjh(PmFwjhVO pmFwjhVO) {
        PmXmjh pmXmjh = new PmXmjh();
        BeanUtils.copyProperties(pmFwjhVO, pmXmjh);
        // 项目计划类型 (1.项目计划填报 2.服务计划填报 3.项目管理单填报)
        pmXmjh.setXmjhlx("2");

        // 1.新增服务相关方
        pmXmjhXgfService.remove(Wrappers.<PmXmjhXgf>lambdaQuery().eq(PmXmjhXgf::getXmjhId, pmXmjh.getId()));
        List<PmXmjhXgf> xgfList = pmFwjhVO.getXgf().stream().peek(pmXmjhXgf -> pmXmjhXgf.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhXgfService.saveBatch(xgfList);

        // 2.新增限制、假设及界外
        pmXmjhXzjsjwService.remove(Wrappers.<PmXmjhXzjsjw>lambdaQuery().eq(PmXmjhXzjsjw::getXmjhId, pmXmjh.getId()));
        List<PmXmjhXzjsjw> xzjsjwsList = pmFwjhVO.getXzjsjw().stream().peek(pmXmjhXzjsjw -> pmXmjhXzjsjw.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhXzjsjwService.saveBatch(xzjsjwsList);

        // 3.新增验收标准和方式
        pmXmjhYsbzfsService.remove(Wrappers.<PmXmjhYsbzfs>lambdaQuery().eq(PmXmjhYsbzfs::getXmjhId, pmXmjh.getId()));
        List<PmXmjhYsbzfs> ysbzfsList = pmFwjhVO.getYsbzfs().stream().peek(pmXmjhYsbzfs -> pmXmjhYsbzfs.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhYsbzfsService.saveBatch(ysbzfsList);

        // 4.新增风险计划
        pmXmjhFxjhService.remove(Wrappers.<PmXmjhFxjh>lambdaQuery().eq(PmXmjhFxjh::getXmjhId, pmXmjh.getId()));
        List<PmXmjhFxjh> fxjhList = pmFwjhVO.getFxjh().stream().peek(pmXmjhFxjh -> {
------------------------------------------------------------------------------------------------------------
            QueryWrapper<PmXmjhFxjh> queryWrapper = new QueryWrapper<>();
            List<PmXmjhFxjh> pmXmjhFxjhsList = pmXmjhFxjhService.list(queryWrapper);
            //获取创建时间最新的值
            int num = 0;
            if(!pmXmjhFxjhsList.isEmpty()) {
                PmXmjhFxjh pmXmjhFxjhs = pmXmjhFxjhsList.stream().map(pmXmjhFxjh1 -> {
                    Long timeTemp = pmXmjhFxjh1.getCreatedTime().toInstant(ZoneOffset.of("+8")).toEpochMilli();
                    pmXmjhFxjh1.setRemark10(timeTemp.toString());
                    return pmXmjhFxjh1;
                }).max(Comparator.comparing(pmXmjhFxjh1 -> pmXmjhFxjh1.getRemark10())).get();
                //截取数字
                num = Integer.parseInt(pmXmjhFxjhs.getFxId().substring(2));
            }
            //调用风险id生成规则
            String str = NoGen.getRiskId(num);
            //设置风险id
            pmXmjhFxjh.setFxId(str);
            pmXmjhFxjh.setXmjhId(pmXmjh.getId());}).collect(Collectors.toList());
---------------------------------------------------------------------------------------------------------
        pmXmjhFxjhService.saveBatch(fxjhList);

        // 5.新增人力资源
        pmXmjhRlzyService.remove(Wrappers.<PmXmjhRlzy>lambdaQuery().eq(PmXmjhRlzy::getXmjhId, pmXmjh.getId()));
        List<PmXmjhRlzy> rlzyList = pmFwjhVO.getRlzy().stream().peek(pmXmjhRlzy -> pmXmjhRlzy.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhRlzyService.saveBatch(rlzyList);

        // 6.新增服务报告
        pmXmjhFwbgService.remove(Wrappers.<PmXmjhFwbg>lambdaQuery().eq(PmXmjhFwbg::getXmjhId, pmXmjh.getId()));
        List<PmXmjhFwbg> fwbgList = pmFwjhVO.getFwbg().stream().peek(pmXmjhFwbg -> pmXmjhFwbg.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhFwbgService.saveBatch(fwbgList);

        // 7.新增工具资源
        pmXmjhGjzyService.remove(Wrappers.<PmXmjhGjzy>lambdaQuery().eq(PmXmjhGjzy::getXmjhId, pmXmjh.getId()));
        List<PmXmjhGjzy> gjzyList = pmFwjhVO.getGjzy().stream().peek(pmXmjhGjzy -> pmXmjhGjzy.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhGjzyService.saveBatch(gjzyList);

        // 8.新增技术支持
        pmXmjhJszcService.remove(Wrappers.<PmXmjhJszc>lambdaQuery().eq(PmXmjhJszc::getXmjhId, pmXmjh.getId()));
        List<PmXmjhJszc> jszcList = pmFwjhVO.getJszc().stream().peek(pmXmjhJszc -> pmXmjhJszc.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhJszcService.saveBatch(jszcList);

        return this.baseMapper.updateById(pmXmjh);
    }

    @Transactional(rollbackFor = Exception.class)
    @Override
    public int deleteFwjh(String id) {

        // 1.删除服务相关方
        pmXmjhXgfService.remove(Wrappers.<PmXmjhXgf>lambdaQuery().eq(PmXmjhXgf::getXmjhId, id));

        // 2.删除限制、假设及界外
        pmXmjhXzjsjwService.remove(Wrappers.<PmXmjhXzjsjw>lambdaQuery().eq(PmXmjhXzjsjw::getXmjhId, id));

        // 3.删除验收标准和方式
        pmXmjhYsbzfsService.remove(Wrappers.<PmXmjhYsbzfs>lambdaQuery().eq(PmXmjhYsbzfs::getXmjhId, id));

        // 4.删除险计划
        pmXmjhFxjhService.remove(Wrappers.<PmXmjhFxjh>lambdaQuery().eq(PmXmjhFxjh::getXmjhId, id));

        // 5.删除人力资源
        pmXmjhRlzyService.remove(Wrappers.<PmXmjhRlzy>lambdaQuery().eq(PmXmjhRlzy::getXmjhId, id));

        // 6.删除服务报告
        pmXmjhFwbgService.remove(Wrappers.<PmXmjhFwbg>lambdaQuery().eq(PmXmjhFwbg::getXmjhId, id));

        // 7.删除工具资源
        pmXmjhGjzyService.remove(Wrappers.<PmXmjhGjzy>lambdaQuery().eq(PmXmjhGjzy::getXmjhId, id));

        // 8.删除技术支持
        pmXmjhJszcService.remove(Wrappers.<PmXmjhJszc>lambdaQuery().eq(PmXmjhJszc::getXmjhId, id));

        return this.baseMapper.deleteById(id);
    }

    @Override
    public PmFwjhVO selectOne(String id) {
        PmFwjhVO pmFwjhVO = new PmFwjhVO();
        QueryWrapper<PmXmjh> queryWrapper = new QueryWrapper<>();
        queryWrapper.lambda().eq(PmXmjh::getId, id).eq(PmXmjh::getXmjhlx, "2");
        PmXmjh pmXmjh = this.baseMapper.selectOne(queryWrapper);
        BeanUtils.copyProperties(pmXmjh, pmFwjhVO);

        // 1.查询服务相关方
        List<PmXmjhXgf> xgfList = pmXmjhXgfService.list(Wrappers.<PmXmjhXgf>lambdaQuery().eq(PmXmjhXgf::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setXgf(xgfList);

        // 2.查询限制、假设及界外
        List<PmXmjhXzjsjw> xzjsjwsList = pmXmjhXzjsjwService.list(Wrappers.<PmXmjhXzjsjw>lambdaQuery().eq(PmXmjhXzjsjw::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setXzjsjw(xzjsjwsList);

        // 3.查询验收标准和方式
        List<PmXmjhYsbzfs> ysbzfsList = pmXmjhYsbzfsService.list(Wrappers.<PmXmjhYsbzfs>lambdaQuery().eq(PmXmjhYsbzfs::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setYsbzfs(ysbzfsList);

        // 4.查询风险计划
        List<PmXmjhFxjh> fxjhList = pmXmjhFxjhService.list(Wrappers.<PmXmjhFxjh>lambdaQuery().eq(PmXmjhFxjh::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setFxjh(fxjhList);

        // 5.查询人力资源
        List<PmXmjhRlzy> rlzyList = pmXmjhRlzyService.list(Wrappers.<PmXmjhRlzy>lambdaQuery().eq(PmXmjhRlzy::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setRlzy(rlzyList);

        // 6.查询服务报告
        List<PmXmjhFwbg> fwbgList = pmXmjhFwbgService.list(Wrappers.<PmXmjhFwbg>lambdaQuery().eq(PmXmjhFwbg::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setFwbg(fwbgList);

        // 7.查询工具资源
        List<PmXmjhGjzy> gjzyList = pmXmjhGjzyService.list(Wrappers.<PmXmjhGjzy>lambdaQuery().eq(PmXmjhGjzy::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setGjzy(gjzyList);

        // 8.查询技术支持
        List<PmXmjhJszc> jszcList = pmXmjhJszcService.list(Wrappers.<PmXmjhJszc>lambdaQuery().eq(PmXmjhJszc::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setJszc(jszcList);

        return pmFwjhVO;
    }
}
