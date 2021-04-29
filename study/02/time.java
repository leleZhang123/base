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

        // ֻ��ѯ����ƻ�� (1.��Ŀ�ƻ�� 2.����ƻ�� 3.��Ŀ�����)
        queryWrapper.lambda().eq(PmXmjh::getXmjhlx, "2");

        // ��Ŀ����
        if (StrUtil.isNotBlank(pmFwjhVO.getXmmc())) {
            queryWrapper.lambda().like(PmXmjh::getXmmc, pmFwjhVO.getXmmc());
        }

        Page<PmFwjhVO> pmFwjhVOPage = pmFwjhMapper.queryPage(page, queryWrapper);

        // ��8���ӱ����ݷŵ�������
        List<PmFwjhVO> pmFwjhVOList = pmFwjhVOPage.getRecords();
        List<PmFwjhVO> collect = pmFwjhVOList.stream().peek(fwjhVO -> {
            // 1.��ѯ������ط�
            List<PmXmjhXgf> xgfList = pmXmjhXgfService.list(Wrappers.<PmXmjhXgf>lambdaQuery().eq(PmXmjhXgf::getXmjhId, fwjhVO.getId()));
            fwjhVO.setXgf(xgfList);

            // 2.��ѯ���ơ����輰����
            List<PmXmjhXzjsjw> xzjsjwsList = pmXmjhXzjsjwService.list(Wrappers.<PmXmjhXzjsjw>lambdaQuery().eq(PmXmjhXzjsjw::getXmjhId, fwjhVO.getId()));
            fwjhVO.setXzjsjw(xzjsjwsList);

            // 3.��ѯ���ձ�׼�ͷ�ʽ
            List<PmXmjhYsbzfs> ysbzfsList = pmXmjhYsbzfsService.list(Wrappers.<PmXmjhYsbzfs>lambdaQuery().eq(PmXmjhYsbzfs::getXmjhId, fwjhVO.getId()));
            fwjhVO.setYsbzfs(ysbzfsList);

            // 4.��ѯ���ռƻ�
            List<PmXmjhFxjh> fxjhList = pmXmjhFxjhService.list(Wrappers.<PmXmjhFxjh>lambdaQuery().eq(PmXmjhFxjh::getXmjhId, fwjhVO.getId()));
            fwjhVO.setFxjh(fxjhList);

            // 5.��ѯ������Դ
            List<PmXmjhRlzy> rlzyList = pmXmjhRlzyService.list(Wrappers.<PmXmjhRlzy>lambdaQuery().eq(PmXmjhRlzy::getXmjhId, fwjhVO.getId()));
            fwjhVO.setRlzy(rlzyList);

            // 6.��ѯ���񱨸�
            List<PmXmjhFwbg> fwbgList = pmXmjhFwbgService.list(Wrappers.<PmXmjhFwbg>lambdaQuery().eq(PmXmjhFwbg::getXmjhId, fwjhVO.getId()));
            fwjhVO.setFwbg(fwbgList);

            // 7.��ѯ������Դ
            List<PmXmjhGjzy> gjzyList = pmXmjhGjzyService.list(Wrappers.<PmXmjhGjzy>lambdaQuery().eq(PmXmjhGjzy::getXmjhId, fwjhVO.getId()));
            fwjhVO.setGjzy(gjzyList);

            // 8.��ѯ����֧��
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

        // ��������ƻ�
        // ��Ŀ�ƻ����� (1.��Ŀ�ƻ�� 2.����ƻ�� 3.��Ŀ�����)
        pmXmjh.setXmjhlx("2");
        this.baseMapper.insert(pmXmjh);

        // 1.����������ط�
        List<PmXmjhXgf> xgfList = pmFwjhVO.getXgf().stream().peek(pmXmjhXgf -> pmXmjhXgf.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhXgfService.saveBatch(xgfList);

        // 2.�������ơ����輰����
        List<PmXmjhXzjsjw> xzjsjwsList = pmFwjhVO.getXzjsjw().stream().peek(pmXmjhXzjsjw -> pmXmjhXzjsjw.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhXzjsjwService.saveBatch(xzjsjwsList);

        // 3.�������ձ�׼�ͷ�ʽ
        List<PmXmjhYsbzfs> ysbzfsList = pmFwjhVO.getYsbzfs().stream().peek(pmXmjhYsbzfs -> pmXmjhYsbzfs.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhYsbzfsService.saveBatch(ysbzfsList);

        // 4.�������ռƻ�
        List<PmXmjhFxjh> fxjhList = pmFwjhVO.getFxjh().stream().peek(pmXmjhFxjh -> {
            QueryWrapper<PmXmjhFxjh> queryWrapper = new QueryWrapper<>();
            List<PmXmjhFxjh> pmXmjhFxjhsList = pmXmjhFxjhService.list(queryWrapper);
            //��ȡ����ʱ�����µ�ֵ
            int num = 0;
            if(!pmXmjhFxjhsList.isEmpty()) {
                PmXmjhFxjh pmXmjhFxjhs = pmXmjhFxjhsList.stream().map(pmXmjhFxjh1 -> {
                    Long timeTemp = pmXmjhFxjh1.getCreatedTime().toInstant(ZoneOffset.of("+8")).toEpochMilli();
                    pmXmjhFxjh1.setRemark10(timeTemp.toString());
                    return pmXmjhFxjh1;
                }).max(Comparator.comparing(pmXmjhFxjh1 -> pmXmjhFxjh1.getRemark10())).get();
                //��ȡ����
                num = Integer.parseInt(pmXmjhFxjhs.getFxId().substring(2));
            }
            //���÷���id���ɹ���
            String str = NoGen.getRiskId(num);
            //���÷���id
            pmXmjhFxjh.setFxId(str);
            pmXmjhFxjh.setXmjhId(pmXmjh.getId()); }).collect(Collectors.toList());
        pmXmjhFxjhService.saveBatch(fxjhList);

        // 5.����������Դ
        List<PmXmjhRlzy> rlzyList = pmFwjhVO.getRlzy().stream().peek(pmXmjhRlzy -> pmXmjhRlzy.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhRlzyService.saveBatch(rlzyList);

        // 6.�������񱨸�
        List<PmXmjhFwbg> fwbgList = pmFwjhVO.getFwbg().stream().peek(pmXmjhFwbg -> pmXmjhFwbg.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhFwbgService.saveBatch(fwbgList);

        // 7.����������Դ
        List<PmXmjhGjzy> gjzyList = pmFwjhVO.getGjzy().stream().peek(pmXmjhGjzy -> pmXmjhGjzy.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhGjzyService.saveBatch(gjzyList);

        // 8.��������֧��
        List<PmXmjhJszc> jszcList = pmFwjhVO.getJszc().stream().peek(pmXmjhJszc -> pmXmjhJszc.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhJszcService.saveBatch(jszcList);

        return 1;
    }

    @Transactional(rollbackFor = Exception.class)
    @Override
    public int updateFwjh(PmFwjhVO pmFwjhVO) {
        PmXmjh pmXmjh = new PmXmjh();
        BeanUtils.copyProperties(pmFwjhVO, pmXmjh);
        // ��Ŀ�ƻ����� (1.��Ŀ�ƻ�� 2.����ƻ�� 3.��Ŀ�����)
        pmXmjh.setXmjhlx("2");

        // 1.����������ط�
        pmXmjhXgfService.remove(Wrappers.<PmXmjhXgf>lambdaQuery().eq(PmXmjhXgf::getXmjhId, pmXmjh.getId()));
        List<PmXmjhXgf> xgfList = pmFwjhVO.getXgf().stream().peek(pmXmjhXgf -> pmXmjhXgf.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhXgfService.saveBatch(xgfList);

        // 2.�������ơ����輰����
        pmXmjhXzjsjwService.remove(Wrappers.<PmXmjhXzjsjw>lambdaQuery().eq(PmXmjhXzjsjw::getXmjhId, pmXmjh.getId()));
        List<PmXmjhXzjsjw> xzjsjwsList = pmFwjhVO.getXzjsjw().stream().peek(pmXmjhXzjsjw -> pmXmjhXzjsjw.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhXzjsjwService.saveBatch(xzjsjwsList);

        // 3.�������ձ�׼�ͷ�ʽ
        pmXmjhYsbzfsService.remove(Wrappers.<PmXmjhYsbzfs>lambdaQuery().eq(PmXmjhYsbzfs::getXmjhId, pmXmjh.getId()));
        List<PmXmjhYsbzfs> ysbzfsList = pmFwjhVO.getYsbzfs().stream().peek(pmXmjhYsbzfs -> pmXmjhYsbzfs.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhYsbzfsService.saveBatch(ysbzfsList);

        // 4.�������ռƻ�
        pmXmjhFxjhService.remove(Wrappers.<PmXmjhFxjh>lambdaQuery().eq(PmXmjhFxjh::getXmjhId, pmXmjh.getId()));
        List<PmXmjhFxjh> fxjhList = pmFwjhVO.getFxjh().stream().peek(pmXmjhFxjh -> {
------------------------------------------------------------------------------------------------------------
            QueryWrapper<PmXmjhFxjh> queryWrapper = new QueryWrapper<>();
            List<PmXmjhFxjh> pmXmjhFxjhsList = pmXmjhFxjhService.list(queryWrapper);
            //��ȡ����ʱ�����µ�ֵ
            int num = 0;
            if(!pmXmjhFxjhsList.isEmpty()) {
                PmXmjhFxjh pmXmjhFxjhs = pmXmjhFxjhsList.stream().map(pmXmjhFxjh1 -> {
                    Long timeTemp = pmXmjhFxjh1.getCreatedTime().toInstant(ZoneOffset.of("+8")).toEpochMilli();
                    pmXmjhFxjh1.setRemark10(timeTemp.toString());
                    return pmXmjhFxjh1;
                }).max(Comparator.comparing(pmXmjhFxjh1 -> pmXmjhFxjh1.getRemark10())).get();
                //��ȡ����
                num = Integer.parseInt(pmXmjhFxjhs.getFxId().substring(2));
            }
            //���÷���id���ɹ���
            String str = NoGen.getRiskId(num);
            //���÷���id
            pmXmjhFxjh.setFxId(str);
            pmXmjhFxjh.setXmjhId(pmXmjh.getId());}).collect(Collectors.toList());
---------------------------------------------------------------------------------------------------------
        pmXmjhFxjhService.saveBatch(fxjhList);

        // 5.����������Դ
        pmXmjhRlzyService.remove(Wrappers.<PmXmjhRlzy>lambdaQuery().eq(PmXmjhRlzy::getXmjhId, pmXmjh.getId()));
        List<PmXmjhRlzy> rlzyList = pmFwjhVO.getRlzy().stream().peek(pmXmjhRlzy -> pmXmjhRlzy.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhRlzyService.saveBatch(rlzyList);

        // 6.�������񱨸�
        pmXmjhFwbgService.remove(Wrappers.<PmXmjhFwbg>lambdaQuery().eq(PmXmjhFwbg::getXmjhId, pmXmjh.getId()));
        List<PmXmjhFwbg> fwbgList = pmFwjhVO.getFwbg().stream().peek(pmXmjhFwbg -> pmXmjhFwbg.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhFwbgService.saveBatch(fwbgList);

        // 7.����������Դ
        pmXmjhGjzyService.remove(Wrappers.<PmXmjhGjzy>lambdaQuery().eq(PmXmjhGjzy::getXmjhId, pmXmjh.getId()));
        List<PmXmjhGjzy> gjzyList = pmFwjhVO.getGjzy().stream().peek(pmXmjhGjzy -> pmXmjhGjzy.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhGjzyService.saveBatch(gjzyList);

        // 8.��������֧��
        pmXmjhJszcService.remove(Wrappers.<PmXmjhJszc>lambdaQuery().eq(PmXmjhJszc::getXmjhId, pmXmjh.getId()));
        List<PmXmjhJszc> jszcList = pmFwjhVO.getJszc().stream().peek(pmXmjhJszc -> pmXmjhJszc.setXmjhId(pmXmjh.getId())).collect(Collectors.toList());
        pmXmjhJszcService.saveBatch(jszcList);

        return this.baseMapper.updateById(pmXmjh);
    }

    @Transactional(rollbackFor = Exception.class)
    @Override
    public int deleteFwjh(String id) {

        // 1.ɾ��������ط�
        pmXmjhXgfService.remove(Wrappers.<PmXmjhXgf>lambdaQuery().eq(PmXmjhXgf::getXmjhId, id));

        // 2.ɾ�����ơ����輰����
        pmXmjhXzjsjwService.remove(Wrappers.<PmXmjhXzjsjw>lambdaQuery().eq(PmXmjhXzjsjw::getXmjhId, id));

        // 3.ɾ�����ձ�׼�ͷ�ʽ
        pmXmjhYsbzfsService.remove(Wrappers.<PmXmjhYsbzfs>lambdaQuery().eq(PmXmjhYsbzfs::getXmjhId, id));

        // 4.ɾ���ռƻ�
        pmXmjhFxjhService.remove(Wrappers.<PmXmjhFxjh>lambdaQuery().eq(PmXmjhFxjh::getXmjhId, id));

        // 5.ɾ��������Դ
        pmXmjhRlzyService.remove(Wrappers.<PmXmjhRlzy>lambdaQuery().eq(PmXmjhRlzy::getXmjhId, id));

        // 6.ɾ�����񱨸�
        pmXmjhFwbgService.remove(Wrappers.<PmXmjhFwbg>lambdaQuery().eq(PmXmjhFwbg::getXmjhId, id));

        // 7.ɾ��������Դ
        pmXmjhGjzyService.remove(Wrappers.<PmXmjhGjzy>lambdaQuery().eq(PmXmjhGjzy::getXmjhId, id));

        // 8.ɾ������֧��
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

        // 1.��ѯ������ط�
        List<PmXmjhXgf> xgfList = pmXmjhXgfService.list(Wrappers.<PmXmjhXgf>lambdaQuery().eq(PmXmjhXgf::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setXgf(xgfList);

        // 2.��ѯ���ơ����輰����
        List<PmXmjhXzjsjw> xzjsjwsList = pmXmjhXzjsjwService.list(Wrappers.<PmXmjhXzjsjw>lambdaQuery().eq(PmXmjhXzjsjw::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setXzjsjw(xzjsjwsList);

        // 3.��ѯ���ձ�׼�ͷ�ʽ
        List<PmXmjhYsbzfs> ysbzfsList = pmXmjhYsbzfsService.list(Wrappers.<PmXmjhYsbzfs>lambdaQuery().eq(PmXmjhYsbzfs::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setYsbzfs(ysbzfsList);

        // 4.��ѯ���ռƻ�
        List<PmXmjhFxjh> fxjhList = pmXmjhFxjhService.list(Wrappers.<PmXmjhFxjh>lambdaQuery().eq(PmXmjhFxjh::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setFxjh(fxjhList);

        // 5.��ѯ������Դ
        List<PmXmjhRlzy> rlzyList = pmXmjhRlzyService.list(Wrappers.<PmXmjhRlzy>lambdaQuery().eq(PmXmjhRlzy::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setRlzy(rlzyList);

        // 6.��ѯ���񱨸�
        List<PmXmjhFwbg> fwbgList = pmXmjhFwbgService.list(Wrappers.<PmXmjhFwbg>lambdaQuery().eq(PmXmjhFwbg::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setFwbg(fwbgList);

        // 7.��ѯ������Դ
        List<PmXmjhGjzy> gjzyList = pmXmjhGjzyService.list(Wrappers.<PmXmjhGjzy>lambdaQuery().eq(PmXmjhGjzy::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setGjzy(gjzyList);

        // 8.��ѯ����֧��
        List<PmXmjhJszc> jszcList = pmXmjhJszcService.list(Wrappers.<PmXmjhJszc>lambdaQuery().eq(PmXmjhJszc::getXmjhId, pmFwjhVO.getId()));
        pmFwjhVO.setJszc(jszcList);

        return pmFwjhVO;
    }
}
